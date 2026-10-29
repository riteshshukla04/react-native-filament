#pragma once

#include "ViewHost.hpp"
#include "utils/ListenerRegistry.hpp"
#include "utils/OnceEvent.hpp"
#include <NitroFilament/HybridSnapshotSpec.hpp>
#include <NitroFilament/NativeSurface.hpp>
#include <NitroFilament/PickResult.hpp>

#include <filament/SwapChain.h>

#include <NitroModules/Promise.hpp>
#include <backend/CallbackHandler.h>

#include <array>
#include <atomic>
#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

namespace margelo::nitro::filament {

class ViewTargetCore final : public ViewHost {
public:
  using PickPromise = Promise<std::optional<PickResult>>;
  using SnapshotPromise = Promise<std::shared_ptr<HybridSnapshotSpec>>;

  /** DEFERRED: the target skipped this frame to keep its frame rate and wants a later one. */
  enum class FrameResult { RENDERED, DEFERRED, NONE };

  ViewTargetCore(::filament::Engine& engine, ::filament::Renderer& renderer, ::filament::backend::CallbackHandler& callbacks,
                 ClearSettings clear);

  void attach(const NativeSurface& surface);
  void resize(const NativeSurface& surface);
  void detach(const NativeSurface& surface);
  bool canRender() const;
  bool hasPendingQueries() const;
  [[nodiscard]] FrameResult render(int64_t frameTimeNanos);
  void setTargetFrameRate(double framesPerSecond);
  double targetFrameRate() const;

  void revoke();
  double width() const;
  double height() const;
  std::function<void()> addResizeListener(std::function<void(double width, double height)> listener);
  std::function<void()> addFirstFrameListener(std::function<void()> listener);
  void pick(double x, double y, PickPromise promise);
  void completePick(uint64_t id, const ::filament::View::PickingQueryResult& result);
  void takeSnapshot(SnapshotPromise promise);
  void completeSnapshot(uint64_t id, std::vector<uint8_t>&& pixels, uint32_t width, uint32_t height);

protected:
  void destroyNative() override;
  double pointsPerPixel() const override;

private:
  void destroySwapChain();
  void readRequestedSnapshots();
  void rejectPendingQueries();
  bool isCurrent(const NativeSurface& surface) const;
  void updateViewport(const NativeSurface& surface);

  ::filament::backend::CallbackHandler& callbacks_;
  ::filament::SwapChain* swapChain_ = nullptr;
  std::optional<NativeSurface> surface_;
  std::atomic<bool> revoked_{false};
  std::atomic<double> width_{0};
  std::atomic<double> height_{0};
  std::atomic<double> targetFrameRate_{0};
  int64_t lastRenderedNanos_ = 0;
  double contentScale_ = 1;
  ListenerRegistry<double, double> resizeListeners_;
  OnceEvent firstFrame_;
  uint64_t nextQueryId_ = 1;
  std::unordered_map<uint64_t, PickPromise> pendingPicks_;
  std::unordered_map<uint64_t, SnapshotPromise> pendingSnapshots_;
  std::vector<uint64_t> requestedSnapshots_;
};

} // namespace margelo::nitro::filament
