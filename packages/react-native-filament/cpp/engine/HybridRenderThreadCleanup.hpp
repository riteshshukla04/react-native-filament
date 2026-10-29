#pragma once

#include <NitroFilament/HybridRenderThreadCleanupSpec.hpp>

#include <atomic>
#include <functional>

namespace margelo::nitro::filament {

class HybridRenderThreadCleanup final : public HybridRenderThreadCleanupSpec {
public:
  explicit HybridRenderThreadCleanup(std::function<void()> cleanup) : cleanup_(std::move(cleanup)) {}

  void run() override;
  void dispose() override;

private:
  std::function<void()> cleanup_;
  std::atomic<bool> taken_{false};
};

} // namespace margelo::nitro::filament
