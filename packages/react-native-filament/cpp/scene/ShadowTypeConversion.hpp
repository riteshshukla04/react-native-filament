#pragma once

#include <NitroFilament/ShadowType.hpp>

#include <filament/Options.h>

namespace margelo::nitro::filament {

::filament::ShadowType toFilamentShadowType(ShadowType type);
ShadowType fromFilamentShadowType(::filament::ShadowType type);

} // namespace margelo::nitro::filament
