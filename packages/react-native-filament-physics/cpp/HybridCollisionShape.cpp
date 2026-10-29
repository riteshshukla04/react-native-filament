#include "HybridCollisionShape.hpp"

#include "BulletConversion.hpp"

namespace margelo::nitro::filament::physics {

std::shared_ptr<HybridCollisionShapeSpec> HybridCollisionShape::of(const std::shared_ptr<EngineExtensionHost>& engine,
                                                                   const std::shared_ptr<CollisionShapeCore>& core) {
  if (std::shared_ptr<HybridCollisionShapeSpec> existing = core->hybrid().lock()) {
    return existing;
  }
  auto created = std::make_shared<HybridCollisionShape>(engine, core);
  core->hybrid() = created;
  return created;
}

HybridCollisionShape::HybridCollisionShape(std::shared_ptr<EngineExtensionHost> engine, std::shared_ptr<CollisionShapeCore> core)
    : engine_(std::move(engine)), core_(std::move(core)) {}

CollisionShapeType HybridCollisionShape::getType() {
  return core_->type();
}

std::tuple<double, double, double> HybridCollisionShape::getLocalScaling() {
  return fromBtVector3(usable("CollisionShape.localScaling").getLocalScaling());
}

void HybridCollisionShape::setLocalScaling(const std::tuple<double, double, double>& localScaling) {
  usable("CollisionShape.localScaling").setLocalScaling(toBtVector3(localScaling));
}

double HybridCollisionShape::getMargin() {
  return usable("CollisionShape.margin").getMargin();
}

void HybridCollisionShape::setMargin(double margin) {
  usable("CollisionShape.margin").setMargin(static_cast<btScalar>(margin));
}

void HybridCollisionShape::dispose() {
  engine_->dispose(core_);
}

const std::shared_ptr<EngineExtensionHost>& HybridCollisionShape::engine() const {
  return engine_;
}

const std::shared_ptr<CollisionShapeCore>& HybridCollisionShape::core() const {
  return core_;
}

btCollisionShape& HybridCollisionShape::usable(const char* method) {
  engine_->requireRenderThread(method);
  core_->requireLive(method);
  return core_->shape();
}

} // namespace margelo::nitro::filament::physics
