import { useDisposableResource, useFilamentContext, useRenderCommit } from 'react-native-filament'
import { Physics } from '../Physics'
import type { PhysicsWorld } from '../specs/PhysicsWorld.nitro'
import type { PhysicsWorldOptions } from '../types/PhysicsWorldOptions'

/**
 * A physics world that steps with the Engine's frames unless `autoStep` is false. It is recreated, with
 * all its bodies, when an option changes, and disposed with its bodies on unmount.
 */
export function useWorld(options: PhysicsWorldOptions = {}): PhysicsWorld | undefined {
  const { engine } = useFilamentContext()
  const commit = useRenderCommit()
  const key = JSON.stringify(options)
  return useDisposableResource(() => {
    const resolved = JSON.parse(key) as PhysicsWorldOptions
    return commit.run(() => {
      'worklet'
      return Physics.createWorld(engine, resolved)
    })
  }, [engine, commit, key])
}
