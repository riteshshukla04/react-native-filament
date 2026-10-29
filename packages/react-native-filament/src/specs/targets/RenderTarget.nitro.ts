import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { ClearOptions } from '../types/ClearOptions'
import type { Camera } from '../scene/Camera.nitro'
import type { Scene } from '../scene/Scene.nitro'
import type { View } from '../scene/View.nitro'

export * from '#nitro/RenderTarget'

/**
 * Renders a Scene through a Camera: a `ViewTarget` into a `FilamentView`, a `Recorder` into an MP4 file.
 */
@Apple({ language: 'c++', allowMultipleImplementations: true, allowInheritance: true })
@Android({ language: 'c++', allowMultipleImplementations: true, allowInheritance: true })
export declare class RenderTarget extends HybridObject {
  /**
   * Width in pixels this target renders at. A `ViewTarget` reports its drawable width, 0 while it has
   * no surface.
   * @thread any
   */
  readonly width: number
  /**
   * Height in pixels this target renders at. A `ViewTarget` reports its drawable height, 0 while it
   * has no surface.
   * @thread any
   */
  readonly height: number
  /**
   * Rendering options of this target. The object is usable from any thread; its members run on the
   * render thread.
   * @thread any
   */
  readonly view: View
  /**
   * Scene this target renders. Without one, the target only clears.
   * @thread render
   */
  setScene(scene: Scene): void
  /** @thread render */
  setCamera(camera: Camera): void
  /**
   * How the target is cleared before each frame.
   * @thread render
   */
  setClearOptions(options: ClearOptions): void
}
