#pragma once

#include <NitroFilamentPhysics/CollisionEventKind.hpp>

#include <memory>

namespace margelo::nitro::filament::physics {

class RigidBodyCore;

struct ContactChange {
  CollisionEventKind kind;
  std::shared_ptr<RigidBodyCore> bodyA;
  std::shared_ptr<RigidBodyCore> bodyB;
};

} // namespace margelo::nitro::filament::physics
