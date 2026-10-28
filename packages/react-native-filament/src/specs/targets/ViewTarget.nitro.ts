import { Android, Apple } from 'react-native-nitro-modules'
import type { ListenerSubscription } from '../types/ListenerSubscription'
import type { PickResult } from '../types/PickResult'
import { RenderTarget } from './RenderTarget.nitro'
import type { Snapshot } from './Snapshot.nitro'

export * from '#nitro/ViewTarget'

/**
 * Renders a Scene through a Camera into a `FilamentView`. Create one with `Engine.createViewTarget()`.
 */
@Apple({ language: 'c++', implementation: { include: '"targets/HybridViewTarget.hpp"', className: 'HybridViewTarget' } })
@Android({ language: 'c++', implementation: { include: '"targets/HybridViewTarget.hpp"', className: 'HybridViewTarget' } })
export declare class ViewTarget extends RenderTarget {
  /**
   * Highest rate in frames per second this target renders at, or `0` to render on every display
   * refresh. Frame listeners and native systems still run on every frame of the Engine.
   * @default 0
   * @thread any
   */
  targetFrameRate: number
  /**
   * Called with the drawable size in pixels whenever it changes, and once right away if the
   * target already has a surface.
   * @thread any
   */
  addOnResizeListener(listener: (width: number, height: number) => void): ListenerSubscription
  /**
   * Called once after this target renders its first frame, or right away if it already has.
   * @thread any
   */
  addOnFirstFrameListener(listener: () => void): ListenerSubscription
  /**
   * The renderable under a point, in points from the top-left corner of the view, or `undefined`
   * if there is none. Resolves after the next rendered frame; rejects with `FilamentDisposedError`
   * if the target is disposed first.
   * @thread any
   */
  pick(x: number, y: number): Promise<PickResult | undefined>
  /**
   * Captures the next rendered frame.
   * @thread any
   */
  takeSnapshot(): Promise<Snapshot>
}
