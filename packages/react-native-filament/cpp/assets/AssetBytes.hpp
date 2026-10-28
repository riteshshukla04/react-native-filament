#pragma once

#include <NitroFilament/AssetUri.hpp>

#include <NitroModules/ArrayBuffer.hpp>
#include <NitroModules/Promise.hpp>

#include <memory>
#include <variant>

namespace margelo::nitro::filament {

using AssetSource = std::variant<ArrayBuffer, AssetUri>;

Promise<ArrayBuffer> readAssetBytes(const AssetSource& source);
std::string temporaryDirectory();

} // namespace margelo::nitro::filament
