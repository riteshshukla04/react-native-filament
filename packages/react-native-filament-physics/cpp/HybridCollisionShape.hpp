#pragma once

#include "CollisionShapeCore.hpp"
#include <NitroFilament/EngineExtension.hpp>
#include <NitroFilamentPhysics/HybridCollisionShapeSpec.hpp>

#include <memory>

namespace margelo::nitro::filament::physics {

class HybridCollisionShape final : public HybridCollisionShapeSpec {
public:
  static std::shared_ptr<HybridCollisionShapeSpec> of(const std::shared_ptr<EngineExtensionHost>& engine,
                                                      const std::shared_ptr<CollisionShapeCore>& core);

  HybridCollisionShape(std::shared_ptr<EngineExtensionHost> engine, std::shared_ptr<CollisionShapeCore> core);

  CollisionShapeType getType() override;
  std::tuple<double, double, double> getLocalScaling() override;
  void setLocalScaling(const std::tuple<double, double, double>& localScaling) override;
  double getMargin() override;
  void setMargin(double margin) override;
  void dispose() override;

  const std::shared_ptr<EngineExtensionHost>& engine() const;
  const std::shared_ptr<CollisionShapeCore>& core() const;

private:
  btCollisionShape& usable(const char* method);

  std::shared_ptr<EngineExtensionHost> engine_;
  std::shared_ptr<CollisionShapeCore> core_;
};

} // namespace margelo::nitro::filament::physics
