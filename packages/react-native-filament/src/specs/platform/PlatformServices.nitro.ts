import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { VideoEncoderOptions } from '../types/VideoEncoderOptions'
import type { AssetIO } from './AssetIO.nitro'
import type { VideoEncoder } from './VideoEncoder.nitro'

export * from '#nitro/PlatformServices'

/**
 * The Swift and Kotlin services the C++ engine calls. Declaring them in this C++ API makes Nitrogen
 * generate the C++ adapters the engine calls them through. Internal to react-native-filament.
 */
@Apple({ language: 'c++', implementation: { include: '"platform/HybridPlatformServices.hpp"', className: 'HybridPlatformServices' } })
@Android({ language: 'c++', implementation: { include: '"platform/HybridPlatformServices.hpp"', className: 'HybridPlatformServices' } })
export declare class PlatformServices extends HybridObject {
  /** The process-wide asset reader. */
  static readonly assetIO: AssetIO
  /** Resolves once the encoder accepts frames. */
  static createVideoEncoder(options: VideoEncoderOptions): Promise<VideoEncoder>
}
