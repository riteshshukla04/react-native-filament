#pragma once

#include "CollisionShapeCore.hpp"
#include <NitroFilament/EngineExtension.hpp>
#include <NitroFilament/Resource.hpp>
#include <NitroFilamentPhysics/ActivationState.hpp>
#include <NitroFilamentPhysics/HybridRigidBodySpec.hpp>

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>

#include <memory>
#include <optional>
#include <string>

namespace margelo::nitro::filament::physics {

class PhysicsWorldCore;

class RigidBodyCore final : public Resource {
public:
  struct Setup {
    std::string id;
    double mass;
    btTransform start;
    double friction;
    double restitution;
    double linearDamping;
    double angularDamping;
    std::optional<double> entity;
  };

  RigidBodyCore(std::shared_ptr<PhysicsWorldCore> world, std::shared_ptr<CollisionShapeCore> shape, const Setup& setup);

  const std::string& id() const;
  double mass() const;
  const std::shared_ptr<CollisionShapeCore>& shape() const;
  btRigidBody& body();
  std::optional<double> entity() const;
  void setEntity(std::optional<double> entity);
  ActivationState activationState() const;
  void setActivationState(ActivationState state);
  void syncEntity(EngineExtensionHost& engine) const;
  std::weak_ptr<HybridRigidBodySpec>& hybrid();

protected:
  void destroyNative() override;

private:
  std::shared_ptr<PhysicsWorldCore> world_;
  const std::shared_ptr<CollisionShapeCore> shape_;
  const std::string id_;
  const double mass_;
  std::unique_ptr<btDefaultMotionState> motionState_;
  std::unique_ptr<btRigidBody> body_;
  std::optional<double> entity_;
  std::weak_ptr<HybridRigidBodySpec> hybrid_;
};

} // namespace margelo::nitro::filament::physics
