import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'

export * from '#nitro/Texture'

/**
 * An image loaded with `Engine.loadTexture()`, for material parameters and background images.
 */
@Apple({ language: 'c++', implementation: { include: '"materials/HybridTexture.hpp"', className: 'HybridTexture' } })
@Android({ language: 'c++', implementation: { include: '"materials/HybridTexture.hpp"', className: 'HybridTexture' } })
export declare class Texture extends HybridObject {
  /** @thread any */
  readonly width: number
  /** @thread any */
  readonly height: number
}
