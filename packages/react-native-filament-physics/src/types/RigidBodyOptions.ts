import type { CollisionShape } from '../specs/CollisionShape.nitro'
import type { Entity, Float3, Quaternion } from 'react-native-filament'

export interface RigidBodyOptions {
  shape: CollisionShape
  /** Kilograms; 0 makes a static body. */
  mass: number
  /** @default [0, 0, 0] */
  position?: Float3
  /** @default [0, 0, 0, 1] */
  rotation?: Quaternion
  /** Reported in collision events. @default '' */
  id?: string
  /** @default 0.5 */
  friction?: number
  /** @default 0 */
  restitution?: number
  /** @default 0 */
  linearDamping?: number
  /** @default 0 */
  angularDamping?: number
  /** An entity whose translation and rotation follow the body after every step. Its scale is kept. */
  entity?: Entity
}
