#pragma once

#include <NitroFilament/FrameInfo.hpp>
#include <NitroFilament/HybridEngineSpec.hpp>
#include <NitroFilament/Resource.hpp>

#include <array>
#include <functional>
#include <memory>

namespace margelo::nitro::filament {

/**
 * Native work that a package extending react-native-filament runs on an Engine's render thread once per
 * frame, after animation players and before skeleton followers and the targets render.
 */
class FrameStage {
public:
  virtual ~FrameStage() = default;

  /** A stopped stage is removed and not called again. */
  virtual bool isStopped() const = 0;
  /** Returns whether the stage needs another frame, which keeps an `on-demand` Engine rendering. */
  virtual bool runFrame(const FrameInfo& frame) = 0;
};

/**
 * The C++ API of an Engine for packages that extend react-native-filament. C++ has no stable ABI, so the
 * extending package must be built against the same version of react-native-filament.
 */
class EngineExtensionHost {
public:
  virtual ~EngineExtensionHost() = default;

  /** The host of an Engine created by react-native-filament. Throws for any other HybridObject. */
  static std::shared_ptr<EngineExtensionHost> of(const std::shared_ptr<HybridEngineSpec>& engine);

  /** Throws a FilamentThreadError unless called on the Engine's render thread. */
  virtual void requireRenderThread(const char* method) const = 0;
  /** Renders a frame in `on-demand` mode. Any thread. */
  virtual void requestFrame() = 0;
  /** Makes `resource` a child of the Engine, which destroys it on shutdown and counts it in `getDebugStats()`. */
  virtual void adopt(const std::shared_ptr<Resource>& resource) = 0;
  /** Marks `resource` and its children disposed and destroys them on the render thread. Any thread. */
  virtual void dispose(const std::shared_ptr<Resource>& resource) = 0;
  /** Calls `stage` every frame until it stops or is released; the Engine holds it weakly. Render thread. */
  virtual void addFrameStage(const std::shared_ptr<FrameStage>& stage) = 0;
  /** Throws a FilamentInvalidEntityError unless `entity` has a transform component. Render thread. */
  virtual void requireTransform(double entity, const char* method) = 0;
  /**
   * Sets the translation and rotation of `entity`'s local transform from the rigid, column-major `matrix`
   * and keeps its scale. Does nothing when `entity` has no transform component. Render thread.
   */
  virtual void setRigidTransform(double entity, const std::array<float, 16>& matrix) = 0;
  /**
   * Runs `body` on the render thread's worklet runtime, where it can call JS callbacks, and drains its
   * microtasks. Returns `false` when the Engine has no runtime. Render thread.
   */
  virtual bool runOnRenderRuntime(const std::function<void()>& body) = 0;
};

} // namespace margelo::nitro::filament
