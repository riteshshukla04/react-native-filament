#pragma once

#include <NitroFilament/AmbientOcclusionOptions.hpp>
#include <NitroFilament/BloomOptions.hpp>
#include <NitroFilament/DynamicResolutionOptions.hpp>
#include <NitroFilament/TemporalAntiAliasingOptions.hpp>

#include <filament/Options.h>

namespace margelo::nitro::filament {

::filament::AmbientOcclusionOptions toFilamentOptions(const AmbientOcclusionOptions& options);
::filament::BloomOptions toFilamentOptions(const BloomOptions& options);
::filament::TemporalAntiAliasingOptions toFilamentOptions(const TemporalAntiAliasingOptions& options);
::filament::DynamicResolutionOptions toFilamentOptions(const DynamicResolutionOptions& options);

} // namespace margelo::nitro::filament
