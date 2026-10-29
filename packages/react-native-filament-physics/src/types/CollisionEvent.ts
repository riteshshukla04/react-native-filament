import type { RigidBody } from '../specs/RigidBody.nitro'
import type { CollisionEventKind } from './CollisionEventKind'

export interface CollisionEvent {
  kind: CollisionEventKind
  bodyA: RigidBody
  bodyB: RigidBody
}
