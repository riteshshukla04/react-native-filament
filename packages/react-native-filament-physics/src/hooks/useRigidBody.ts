import { useDisposableResource, useRenderCommit } from 'react-native-filament'
import type { PhysicsWorld } from '../specs/PhysicsWorld.nitro'
import type { RigidBody } from '../specs/RigidBody.nitro'
import type { RigidBodyOptions } from '../types/RigidBodyOptions'

/**
 * A rigid body in `world`, created once `world` and `options` exist and recreated when an option
 * changes. Disposed on unmount.
 */
export function useRigidBody(world: PhysicsWorld | undefined, options: RigidBodyOptions | undefined): RigidBody | undefined {
  const commit = useRenderCommit()
  const shape = options?.shape
  const key = options == null ? undefined : JSON.stringify({ ...options, shape: undefined })
  return useDisposableResource(() => {
    if (world == null || shape == null || key == null) return undefined
    const resolved = { ...(JSON.parse(key) as Omit<RigidBodyOptions, 'shape'>), shape }
    return commit.run(() => {
      'worklet'
      return world.createRigidBody(resolved)
    })
  }, [commit, world, shape, key])
}
