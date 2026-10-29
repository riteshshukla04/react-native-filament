#include "HybridPlatformServices.hpp"

namespace margelo::nitro::filament {

HybridAssetIOSpecCxx HybridPlatformServices::getAssetIO() {
  static const HybridAssetIOSpecCxx assetIO = HybridAssetIOSpecCxx::create();
  return assetIO;
}

Promise<HybridVideoEncoderSpecCxx> HybridPlatformServices::createVideoEncoder(const VideoEncoderOptions& options) {
  return HybridVideoEncoderSpecCxx::create(options);
}

} // namespace margelo::nitro::filament
