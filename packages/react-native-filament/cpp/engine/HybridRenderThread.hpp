#pragma once

#include "EngineCore.hpp"
#include <NitroFilament/HybridRenderThreadSpec.hpp>

#include <memory>

namespace margelo::nitro::filament {

class HybridRenderThread final : public HybridRenderThreadSpec {
public:
  struct Class {
    using Base = HybridRenderThreadSpec::Class;
    static constexpr const char* name = "RenderThread";
    static const std::shared_ptr<const HybridClass>& get();
  };

  explicit HybridRenderThread(std::shared_ptr<EngineCore> engine) : engine_(std::move(engine)) {}

  bool getIsCurrentThread() override;
  bool getHasRuntime() override;
  std::shared_ptr<HybridRenderThreadCleanupSpec> retainCleanup(const Callback<void()>& cleanup) override;

protected:
  const std::shared_ptr<const HybridClass>& getHybridClass() override {
    return Class::get();
  }

private:
  jsi::Value createQueue(jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count);
  jsi::Value bindRuntime(jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count);
  jsi::Value bindPooledRuntime(jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count);
  jsi::Value runAsync(jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count);

  std::shared_ptr<EngineCore> engine_;
};

} // namespace margelo::nitro::filament
