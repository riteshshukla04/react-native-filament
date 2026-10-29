#pragma once

#include <NitroFilamentPhysics/HybridPhysicsFactorySpec.hpp>

#include <memory>

namespace margelo::nitro::filament::physics {

class HybridPhysicsFactory final : public HybridPhysicsFactorySpec {
public:
  HybridPhysicsFactory() {}

  std::shared_ptr<HybridPhysicsWorldSpec> createWorld(const std::shared_ptr<HybridEngineSpec>& engine,
                                                      const PhysicsWorldOptions& options) override;
};

} // namespace margelo::nitro::filament::physics
