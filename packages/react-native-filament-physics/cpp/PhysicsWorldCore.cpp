#include "PhysicsWorldCore.hpp"

#include <algorithm>

namespace margelo::nitro::filament::physics {

PhysicsWorldCore::PhysicsWorldCore(std::shared_ptr<EngineExtensionHost> engine, Settings settings)
    : Resource("PhysicsWorld"), engine_(std::move(engine)), settings_(settings),
      configuration_(std::make_unique<btDefaultCollisionConfiguration>()),
      dispatcher_(std::make_unique<btCollisionDispatcher>(configuration_.get())), broadphase_(std::make_unique<btDbvtBroadphase>()),
      solver_(std::make_unique<btSequentialImpulseConstraintSolver>()),
      world_(std::make_unique<btDiscreteDynamicsWorld>(dispatcher_.get(), broadphase_.get(), solver_.get(), configuration_.get())) {
  world_->setGravity(settings_.gravity);
  world_->setLatencyMotionStateInterpolation(false);
}

const std::shared_ptr<EngineExtensionHost>& PhysicsWorldCore::engine() const {
  return engine_;
}

bool PhysicsWorldCore::isStopped() const {
  return !isLive();
}

bool PhysicsWorldCore::runFrame(const FrameInfo& frame) {
  return settings_.autoStep && step(frame.deltaSeconds);
}

btDiscreteDynamicsWorld& PhysicsWorldCore::world() {
  return *world_;
}

size_t PhysicsWorldCore::bodyCount() const {
  return bodyCount_;
}

std::shared_ptr<CollisionShapeCore> PhysicsWorldCore::adoptShape(std::shared_ptr<CollisionShapeCore> shape) {
  adopt(shape);
  return shape;
}

std::shared_ptr<RigidBodyCore> PhysicsWorldCore::createBody(const std::shared_ptr<CollisionShapeCore>& shape,
                                                            const RigidBodyCore::Setup& setup) {
  auto self = std::static_pointer_cast<PhysicsWorldCore>(shared_from_this());
  auto body = std::make_shared<RigidBodyCore>(self, shape, setup);
  world_->addRigidBody(&body->body());
  bodies_.push_back(body);
  bodyCount_ = bodies_.size();
  adopt(body);
  return body;
}

void PhysicsWorldCore::detach(RigidBodyCore& body) {
  contacts_.forget(&body);
  world_->removeRigidBody(&body.body());
  std::erase_if(bodies_, [&](const std::shared_ptr<RigidBodyCore>& existing) { return existing.get() == &body; });
  bodyCount_ = bodies_.size();
}

std::shared_ptr<CollisionListeners::Entry> PhysicsWorldCore::addCollisionListener(CollisionListeners::Listener callback) {
  return collisionListeners_.add(std::move(callback));
}

bool PhysicsWorldCore::step(double deltaSeconds) {
  world_->stepSimulation(static_cast<btScalar>(deltaSeconds), settings_.maxSubSteps, static_cast<btScalar>(settings_.fixedTimeStepSeconds));
  bool active = false;
  for (const std::shared_ptr<RigidBodyCore>& body : bodies_) {
    body->syncEntity(*engine_);
    active = active || body->body().isActive();
  }
  std::vector<ContactChange> changes = contacts_.update(*dispatcher_);
  if (!changes.empty() && !collisionListeners_.empty()) {
    engine_->runOnRenderRuntime([&] { collisionListeners_.dispatch(changes); });
  }
  return active;
}

void PhysicsWorldCore::destroyNative() {
  collisionListeners_.clear();
  world_ = nullptr;
  solver_ = nullptr;
  broadphase_ = nullptr;
  dispatcher_ = nullptr;
  configuration_ = nullptr;
}

} // namespace margelo::nitro::filament::physics
