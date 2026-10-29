import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { AnimationInfo } from '../types/AnimationInfo'
import type { AnimationPlayer } from './AnimationPlayer.nitro'

export * from '#nitro/Animator'

/**
 * Applies the glTF animations of one model instance. Get it from `ModelInstance.animator`; apply
 * animations from a render-thread worklet or use `createPlayer()` to play them natively.
 */
@Apple({ language: 'c++', implementation: { include: '"assets/HybridAnimator.hpp"', className: 'HybridAnimator' } })
@Android({ language: 'c++', implementation: { include: '"assets/HybridAnimator.hpp"', className: 'HybridAnimator' } })
export declare class Animator extends HybridObject {
  /** @thread any */
  readonly animations: AnimationInfo[]
  /** @thread render */
  applyAnimation(animationIndex: number, timeSeconds: number): void
  /**
   * Blends the previous animation at `previousTimeSeconds` into the pose from `applyAnimation`.
   * `alpha` 0 shows only the previous animation and 1 only the current one. Call it after
   * `applyAnimation` and before `updateBoneMatrices`.
   * @thread render
   */
  applyCrossFade(previousIndex: number, previousTimeSeconds: number, alpha: number): void
  /** @thread render */
  updateBoneMatrices(): void
  /** @thread render */
  resetBoneMatrices(): void
  /**
   * A player that animates this instance natively, without JS per frame.
   * @thread any
   */
  createPlayer(): AnimationPlayer
}
