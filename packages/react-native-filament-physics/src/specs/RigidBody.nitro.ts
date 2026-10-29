import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { ActivationState } from '../types/ActivationState'
import type { Entity, Float3, Mat4 } from 'react-native-filament'
import type { CollisionShape } from './CollisionShape.nitro'

export * from '#nitro/RigidBody'

/**
 * A body in a `PhysicsWorld`. The world keeps it until `dispose()` or until the world is disposed.
 * Every member except `id`, `mass` and `shape` runs on the render thread. Changing a body does not
 * request a frame: in `on-demand` mode, call `engine.requestFrame()` after waking a resting body.
 */
@Apple({ language: 'c++', implementation: { include: '"HybridRigidBody.hpp"', className: 'HybridRigidBody' } })
@Android({ language: 'c++', implementation: { include: '"HybridRigidBody.hpp"', className: 'HybridRigidBody' } })
export declare class RigidBody extends HybridObject {
  /** @thread any */
  readonly id: string
  /** @thread any */
  readonly mass: number
  /** @thread any */
  readonly shape: CollisionShape
  friction: number
  restitution: number
  activationState: ActivationState
  /** Meters per second. */
  linearVelocity: Float3
  /** Radians per second around each axis. */
  angularVelocity: Float3
  /** The entity that follows this body after every step, or `undefined`. */
  entity: Entity | undefined
  setDamping(linear: number, angular: number): void
  applyCentralImpulse(impulse: Float3): void
  applyCentralForce(force: Float3): void
  /** The body's world transform, without scale. */
  getTransform(): Mat4
  /** Moves the body; scale in `transform` is ignored. */
  setTransform(transform: Mat4): void
}
