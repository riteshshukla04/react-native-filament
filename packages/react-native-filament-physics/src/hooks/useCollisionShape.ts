import type { DependencyList } from 'react'
import { useDisposableResource, useRenderCommit } from 'react-native-filament'
import type { CollisionShape } from '../specs/CollisionShape.nitro'
import type { PhysicsWorld } from '../specs/PhysicsWorld.nitro'

export function useCollisionShape(
  world: PhysicsWorld | undefined,
  create: (world: PhysicsWorld) => CollisionShape,
  deps: DependencyList
): CollisionShape | undefined {
  const commit = useRenderCommit()
  return useDisposableResource(() => {
    if (world == null) return undefined
    return commit.run(() => {
      'worklet'
      return create(world)
    })
  }, [commit, world, ...deps])
}
