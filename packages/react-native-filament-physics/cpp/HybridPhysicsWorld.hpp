#pragma once

#include "PhysicsWorldCore.hpp"
#include <NitroFilament/EngineExtension.hpp>
#include <NitroFilamentPhysics/HybridPhysicsWorldSpec.hpp>

#include <memory>

namespace margelo::nitro::filament::physics {

class HybridPhysicsWorld final : public HybridPhysicsWorldSpec {
public:
  HybridPhysicsWorld(std::shared_ptr<EngineExtensionHost> engine, std::shared_ptr<PhysicsWorldCore> core);

  std::tuple<double, double, double> getGravity() override;
  void setGravity(const std::tuple<double, double, double>& gravity) override;
  double getBodyCount() override;
  std::shared_ptr<HybridCollisionShapeSpec> createBoxShape(const std::tuple<double, double, double>& halfExtent) override;
  std::shared_ptr<HybridCollisionShapeSpec> createSphereShape(double radius) override;
  std::shared_ptr<HybridCollisionShapeSpec> createCylinderShape(const std::tuple<double, double, double>& halfExtent,
                                                                CylinderAxis axis) override;
  std::shared_ptr<HybridCollisionShapeSpec> createStaticPlaneShape(const std::tuple<double, double, double>& normal,
                                                                   double constant) override;
  std::shared_ptr<HybridRigidBodySpec> createRigidBody(const RigidBodyOptions& options) override;
  void step(double deltaSeconds) override;
  ListenerSubscription addOnCollisionListener(const Callback<bool(const std::vector<CollisionEvent>&)>& listener) override;
  void dispose() override;
  size_t getExternalMemorySize() noexcept override;

private:
  PhysicsWorldCore& usable(const char* method);
  std::shared_ptr<HybridCollisionShapeSpec> adoptShape(std::shared_ptr<CollisionShapeCore> shape);

  std::shared_ptr<EngineExtensionHost> engine_;
  std::shared_ptr<PhysicsWorldCore> core_;
};

} // namespace margelo::nitro::filament::physics
