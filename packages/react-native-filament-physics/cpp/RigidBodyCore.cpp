#include "RigidBodyCore.hpp"

#include "BulletConversion.hpp"
#include "PhysicsWorldCore.hpp"

namespace margelo::nitro::filament::physics {

namespace {

  btRigidBody::btRigidBodyConstructionInfo constructionInfo(const RigidBodyCore::Setup& setup, btMotionState* motionState,
                                                            btCollisionShape& shape) {
    btVector3 inertia(0, 0, 0);
    if (setup.mass > 0) {
      shape.calculateLocalInertia(static_cast<btScalar>(setup.mass), inertia);
    }
    btRigidBody::btRigidBodyConstructionInfo info(static_cast<btScalar>(setup.mass), motionState, &shape, inertia);
    info.m_friction = static_cast<btScalar>(setup.friction);
    info.m_restitution = static_cast<btScalar>(setup.restitution);
    info.m_linearDamping = static_cast<btScalar>(setup.linearDamping);
    info.m_angularDamping = static_cast<btScalar>(setup.angularDamping);
    return info;
  }

} // namespace

RigidBodyCore::RigidBodyCore(std::shared_ptr<PhysicsWorldCore> world, std::shared_ptr<CollisionShapeCore> shape, const Setup& setup)
    : Resource("RigidBody"), world_(std::move(world)), shape_(std::move(shape)), id_(setup.id), mass_(setup.mass),
      motionState_(std::make_unique<btDefaultMotionState>(setup.start)),
      body_(std::make_unique<btRigidBody>(constructionInfo(setup, motionState_.get(), shape_->shape()))), entity_(setup.entity) {
  body_->setUserPointer(this);
}

const std::string& RigidBodyCore::id() const {
  return id_;
}

double RigidBodyCore::mass() const {
  return mass_;
}

const std::shared_ptr<CollisionShapeCore>& RigidBodyCore::shape() const {
  return shape_;
}

btRigidBody& RigidBodyCore::body() {
  return *body_;
}

std::optional<double> RigidBodyCore::entity() const {
  return entity_;
}

void RigidBodyCore::setEntity(std::optional<double> entity) {
  entity_ = entity;
}

ActivationState RigidBodyCore::activationState() const {
  switch (body_->getActivationState()) {
    case ISLAND_SLEEPING:
      return ActivationState::SLEEPING;
    case WANTS_DEACTIVATION:
      return ActivationState::WANTS_SLEEP;
    case DISABLE_DEACTIVATION:
      return ActivationState::NEVER_SLEEP;
    case DISABLE_SIMULATION:
      return ActivationState::SIMULATION_DISABLED;
    default:
      return ActivationState::ACTIVE;
  }
}

void RigidBodyCore::setActivationState(ActivationState state) {
  switch (state) {
    case ActivationState::ACTIVE:
      body_->forceActivationState(ACTIVE_TAG);
      body_->activate(true);
      break;
    case ActivationState::SLEEPING:
      body_->forceActivationState(ISLAND_SLEEPING);
      break;
    case ActivationState::WANTS_SLEEP:
      body_->forceActivationState(WANTS_DEACTIVATION);
      break;
    case ActivationState::NEVER_SLEEP:
      body_->forceActivationState(DISABLE_DEACTIVATION);
      break;
    case ActivationState::SIMULATION_DISABLED:
      body_->forceActivationState(DISABLE_SIMULATION);
      break;
  }
}

void RigidBodyCore::syncEntity(EngineExtensionHost& engine) const {
  if (!entity_.has_value()) {
    return;
  }
  btTransform worldTransform;
  motionState_->getWorldTransform(worldTransform);
  engine.setRigidTransform(*entity_, toColumnMajor(worldTransform));
}

std::weak_ptr<HybridRigidBodySpec>& RigidBodyCore::hybrid() {
  return hybrid_;
}

void RigidBodyCore::destroyNative() {
  world_->detach(*this);
  world_ = nullptr;
  body_ = nullptr;
  motionState_ = nullptr;
}

} // namespace margelo::nitro::filament::physics
