import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { CollisionShapeType } from '../types/CollisionShapeType'
import type { Float3 } from 'react-native-filament'

export * from '#nitro/CollisionShape'

/** A shape that rigid bodies share. It lives as long as a body or JS uses it. */
@Apple({ language: 'c++', implementation: { include: '"HybridCollisionShape.hpp"', className: 'HybridCollisionShape' } })
@Android({ language: 'c++', implementation: { include: '"HybridCollisionShape.hpp"', className: 'HybridCollisionShape' } })
export declare class CollisionShape extends HybridObject {
  /** @thread any */
  readonly type: CollisionShapeType
  /** @thread render */
  localScaling: Float3
  /** Collision margin in meters. @thread render */
  margin: number
}
