import { Android, Apple, type HybridView } from 'react-native-nitro-modules'
import type { SurfaceObserver } from '../types/SurfaceObserver'

export * from '#nitro/FilamentView'

/**
 * The native view Filament renders into. Pass it to `Engine.createViewTarget()`.
 */
@Apple({ language: 'swift', implementation: { className: 'HybridFilamentView' } })
@Android({ language: 'kotlin', implementation: { className: 'HybridFilamentView' } })
export declare class FilamentView extends HybridView {
  /**
   * Composite with the views behind it. Uses a `TextureView` on Android.
   * @default false
   */
  transparent?: boolean
  /**
   * Internal: a ViewTarget observes the view's surfaces through this.
   */
  setSurfaceObserver(observer: SurfaceObserver | undefined): void
}
