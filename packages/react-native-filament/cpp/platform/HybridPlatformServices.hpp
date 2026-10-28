#pragma once

#include <NitroFilament/HybridAssetIOSpecCxx.hpp>
#include <NitroFilament/HybridPlatformServicesSpec.hpp>
#include <NitroFilament/HybridVideoEncoderSpecCxx.hpp>
#include <NitroFilament/VideoEncoderOptions.hpp>
#include <NitroModules/Promise.hpp>

namespace margelo::nitro::filament {

class HybridPlatformServices final : public HybridPlatformServicesSpec {
public:
  static HybridAssetIOSpecCxx getAssetIO();
  static Promise<HybridVideoEncoderSpecCxx> createVideoEncoder(const VideoEncoderOptions& options);
};

} // namespace margelo::nitro::filament
