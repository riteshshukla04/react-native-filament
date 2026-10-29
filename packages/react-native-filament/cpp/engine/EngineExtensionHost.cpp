#include <NitroFilament/EngineExtension.hpp>

#include "HybridEngine.hpp"

#include <stdexcept>

namespace margelo::nitro::filament {

std::shared_ptr<EngineExtensionHost> EngineExtensionHost::of(const std::shared_ptr<HybridEngineSpec>& engine) {
  std::shared_ptr<HybridEngine> hybrid = std::dynamic_pointer_cast<HybridEngine>(engine);
  if (hybrid == nullptr) {
    throw std::invalid_argument("EngineExtensionHost::of() needs an Engine created by react-native-filament.");
  }
  return hybrid->core();
}

} // namespace margelo::nitro::filament
