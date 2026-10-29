import { useContext } from 'react'
import { RenderCommitContext } from './RenderCommitContext'
import type { RenderCommit } from './RenderCommit'

/**
 * The render-thread queue of the closest `<FilamentScene>`. `run(worklet)` runs the worklet on the
 * render thread together with the other work React submits in the same commit, in submission order.
 * Hooks of packages that extend react-native-filament use it so their work stays ordered with the
 * components'.
 */
export function useRenderCommit(): RenderCommit {
  const commit = useContext(RenderCommitContext)
  if (commit == null) {
    throw new Error('Filament hooks and components must be used inside a <FilamentScene>.')
  }
  return commit
}
