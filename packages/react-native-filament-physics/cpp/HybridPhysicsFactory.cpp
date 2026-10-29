#include "HybridPhysicsFactory.hpp"

#include "HybridPhysicsWorld.hpp"

#include <NitroFilament/EngineExtension.hpp>

#include <stdexcept>
#include <string>

namespace margelo::nitro::filament::physics {

std::shared_ptr<HybridPhysicsWorldSpec> HybridPhysicsFactory::createWorld(const std::shared_ptr<HybridEngineSpec>& engine,
                                                                          const PhysicsWorldOptions& options) {
  constexpr const char* method = "Physics.createWorld()";
  std::shared_ptr<EngineExtensionHost> host = EngineExtensionHost::of(engine);
  host->requireRenderThread(method);
  double fixedTimeStep = options.fixedTimeStepSeconds.value_or(1.0 / 60.0);
  double maxSubSteps = options.maxSubSteps.value_or(4);
  if (!(fixedTimeStep > 0) || !(maxSubSteps >= 1)) {
    throw std::invalid_argument(std::string(method) + " needs a positive fixed time step and at least one sub-step.");
  }
  auto [x, y, z] = options.gravity.value_or(std::make_tuple(0.0, -9.81, 0.0));
  PhysicsWorldCore::Settings settings{.gravity = btVector3(static_cast<btScalar>(x), static_cast<btScalar>(y), static_cast<btScalar>(z)),
                                      .fixedTimeStepSeconds = fixedTimeStep,
                                      .maxSubSteps = static_cast<int>(maxSubSteps),
                                      .autoStep = options.autoStep.value_or(true)};
  auto world = std::make_shared<PhysicsWorldCore>(host, settings);
  host->adopt(world);
  host->addFrameStage(world);
  return std::make_shared<HybridPhysicsWorld>(std::move(host), std::move(world));
}

} // namespace margelo::nitro::filament::physics
