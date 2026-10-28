#pragma once

#include <NitroFilament/HybridAssetIOSpec.hpp>

namespace margelo::nitro::filament {

/** Memory-maps files and bundled assets, and downloads URLs to the caches directory first. */
class HybridAssetIO final : public HybridAssetIOSpec {
public:
  HybridAssetIO() = default;

  std::string getTemporaryDirectory() override;
  Promise<ArrayBuffer> read(const std::string& uri) override;
};

} // namespace margelo::nitro::filament
