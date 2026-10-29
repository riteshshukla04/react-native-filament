#include "HybridRenderThread.hpp"

#include "HybridRenderThreadCleanup.hpp"
#include "RenderThreadQueue.hpp"

#include <NitroModules/Callback.hpp>
#include <NitroModules/HybridClass.hpp>
#include <NitroModules/JSIConverter.hpp>

namespace margelo::nitro::filament {

bool HybridRenderThread::getIsCurrentThread() {
  return engine_->thread().isCurrentThread();
}

bool HybridRenderThread::getHasRuntime() {
  return engine_->hasRuntime();
}

std::shared_ptr<HybridRenderThreadCleanupSpec> HybridRenderThread::retainCleanup(const Callback<void()>& cleanup) {
  return std::make_shared<HybridRenderThreadCleanup>(cleanup);
}

const std::shared_ptr<const HybridClass>& HybridRenderThread::Class::get() {
  static const auto hybridClass = HybridClass::create<Class>([](HybridClass& clazz) {
    clazz.registerRawHybridMethod("createQueue", 0, &HybridRenderThread::createQueue);
    clazz.registerRawHybridMethod("bindRuntime", 1, &HybridRenderThread::bindRuntime);
    clazz.registerRawHybridMethod("bindPooledRuntime", 0, &HybridRenderThread::bindPooledRuntime);
    clazz.registerRawHybridMethod("runAsync", 2, &HybridRenderThread::runAsync);
  });
  return hybridClass;
}

jsi::Value HybridRenderThread::createQueue(jsi::Runtime& runtime, const jsi::Value&, const jsi::Value*, size_t) {
  jsi::Object queue(runtime);
  queue.setNativeState(runtime, engine_->createRuntimeQueue());
  return queue;
}

jsi::Value HybridRenderThread::bindRuntime(jsi::Runtime& runtime, const jsi::Value&, const jsi::Value* args, size_t) {
  engine_->bindRuntime(worklets::extractWorkletRuntime(runtime, args[0]));
  return jsi::Value::undefined();
}

jsi::Value HybridRenderThread::bindPooledRuntime(jsi::Runtime&, const jsi::Value&, const jsi::Value*, size_t) {
  return jsi::Value(engine_->bindPooledRuntime());
}

jsi::Value HybridRenderThread::runAsync(jsi::Runtime& runtime, const jsi::Value&, const jsi::Value* args, size_t) {
  auto worklet =
      worklets::extractSerializableOrThrow<worklets::SerializableWorklet>(runtime, args[0], "runOnRenderThread() expects a worklet.");
  auto onCancelled = JSIConverter<Callback<void(std::string)>>::fromJSI(runtime, args[1]);
  std::shared_ptr<EngineCore> engine = engine_;
  engine->thread().post({
      .run =
          [engine, worklet, onCancelled] {
            if (!engine->isLive()) {
              onCancelled("FilamentDisposedError: The Engine was shut down before the job ran.");
              return;
            }
            engine->runWorklet(worklet);
          },
      .cancel = [onCancelled] { onCancelled("FilamentDisposedError: The Engine was shut down before the job ran."); },
  });
  return jsi::Value::undefined();
}

} // namespace margelo::nitro::filament
