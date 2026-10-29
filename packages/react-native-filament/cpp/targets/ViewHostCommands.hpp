#pragma once

#include "ViewHost.hpp"
#include "engine/EngineCore.hpp"
#include <NitroFilament/ClearOptions.hpp>
#include <NitroFilament/HybridCameraSpec.hpp>
#include <NitroFilament/HybridSceneSpec.hpp>

#include <memory>
#include <optional>

namespace margelo::nitro::filament {

ViewHost::ClearSettings toClearSettings(const std::optional<ClearOptions>& options);
void setHostScene(ViewHost& host, const EngineCore& engine, const std::shared_ptr<HybridSceneSpec>& scene, const char* method);
void setHostCamera(ViewHost& host, const EngineCore& engine, const std::shared_ptr<HybridCameraSpec>& camera, const char* method);

} // namespace margelo::nitro::filament
