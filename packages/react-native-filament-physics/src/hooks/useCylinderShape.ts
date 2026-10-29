import type { CollisionShape } from '../specs/CollisionShape.nitro'
import type { PhysicsWorld } from '../specs/PhysicsWorld.nitro'
import type { CylinderAxis } from '../types/CylinderAxis'
import type { Float3 } from 'react-native-filament'
import { useCollisionShape } from './useCollisionShape'

/**
 * A cylinder shape in `world` with half extents in meters along `axis`, created once `world` exists,
 * recreated when an argument changes and disposed on unmount.
 * @param axis The cylinder's axis. Defaults to `'y'`.
 */
export function useCylinderShape(
  world: PhysicsWorld | undefined,
  halfExtent: Float3,
  axis: CylinderAxis = 'y'
): CollisionShape | undefined {
  const [x, y, z] = halfExtent
  return useCollisionShape(
    world,
    (target) => {
      'worklet'
      return target.createCylinderShape([x, y, z], axis)
    },
    [x, y, z, axis]
  )
}
