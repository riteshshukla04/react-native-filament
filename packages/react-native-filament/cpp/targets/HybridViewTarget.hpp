#pragma once

#include "ViewTargetCore.hpp"
#include <NitroFilament/HybridFilamentViewSpecCxx.hpp>
#include <NitroFilament/HybridViewTargetSpec.hpp>
#include <NitroFilament/SurfaceObserver.hpp>

#include <atomic>
#include <memory>

namespace margelo::nitro::filament {

class HybridEngine;
class EngineCore;

class HybridViewTarget final : public HybridViewTargetSpec {
public:
  HybridViewTarget(std::shared_ptr<HybridEngine> engine, std::shared_ptr<ViewTargetCore> core, HybridFilamentViewSpecCxx view);
  ~HybridViewTarget() override;

  double getWidth() override;
  double getHeight() override;
  std::shared_ptr<HybridViewSpec> getView() override;
  double getTargetFrameRate() override;
  void setTargetFrameRate(double targetFrameRate) override;
  ListenerSubscription addOnFirstFrameListener(const Callback<void()>& listener) override;
  Promise<std::optional<PickResult>> pick(double x, double y) override;
  Promise<std::shared_ptr<HybridSnapshotSpec>> takeSnapshot() override;
  ListenerSubscription addOnResizeListener(const Callback<void(double width, double height)>& listener) override;
  void setScene(const std::shared_ptr<HybridSceneSpec>& scene) override;
  void setCamera(const std::shared_ptr<HybridCameraSpec>& camera) override;
  void setClearOptions(const ClearOptions& options) override;
  void dispose() override;
  size_t getExternalMemorySize() noexcept override;

private:
  static SurfaceObserver makeSurfaceObserver(std::weak_ptr<EngineCore> engine, std::weak_ptr<ViewTargetCore> target);

  std::shared_ptr<HybridEngine> engine_;
  std::shared_ptr<ViewTargetCore> core_;
  HybridFilamentViewSpecCxx view_;
  std::shared_ptr<HybridViewSpec> renderView_;
  std::atomic<bool> disposed_{false};
};

} // namespace margelo::nitro::filament
