#pragma once

#include "SnapshotCore.hpp"
#include <NitroFilament/HybridSnapshotSpec.hpp>

#include <memory>

namespace margelo::nitro::filament {

class HybridSnapshot final : public HybridSnapshotSpec {
public:
  explicit HybridSnapshot(std::shared_ptr<const SnapshotCore> core);

  double getWidth() override;
  double getHeight() override;
  ArrayBuffer toArrayBuffer() override;
  Promise<std::string> saveToTemporaryFile() override;
  size_t getExternalMemorySize() noexcept override;

private:
  std::shared_ptr<const SnapshotCore> core_;
};

} // namespace margelo::nitro::filament
