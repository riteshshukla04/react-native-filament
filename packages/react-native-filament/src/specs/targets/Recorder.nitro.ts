import { Android, Apple } from 'react-native-nitro-modules'
import { RenderTarget } from './RenderTarget.nitro'

export * from '#nitro/Recorder'

/**
 * Renders a scene offscreen into an H.264 MP4 file, as fast as the encoder accepts frames. Create
 * it on an Engine dedicated to recording: while a recording runs, that Engine renders only the
 * recorder's frames and its view targets pause.
 */
@Apple({ language: 'c++', implementation: { include: '"targets/HybridRecorder.hpp"', className: 'HybridRecorder' } })
@Android({ language: 'c++', implementation: { include: '"targets/HybridRecorder.hpp"', className: 'HybridRecorder' } })
export declare class Recorder extends RenderTarget {
  /** @thread any */
  readonly fps: number
  /**
   * Renders `frameCount` frames and resolves with the `file://` URI of the finished MP4 in the
   * temporary directory. Before each frame the Engine runs its bindings, frame listeners and
   * animation players on a fixed clock: frame `i` has `elapsedSeconds = i / fps` and
   * `deltaSeconds = 1 / fps` (0 for the first frame). Rejects with `FilamentBusyError` while this
   * recorder is already recording, and with `FilamentDisposedError` when the recorder or its Engine
   * is disposed first.
   * @thread any
   */
  record(frameCount: number): Promise<string>
}
