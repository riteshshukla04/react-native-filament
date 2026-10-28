import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'

export * from '#nitro/IndirectLight'

/**
 * Image-based lighting loaded from a KTX file with `Engine.loadIndirectLight()`. Apply it with
 * `Scene.setIndirectLight()`.
 */
@Apple({ language: 'c++', implementation: { include: '"scene/HybridIndirectLight.hpp"', className: 'HybridIndirectLight' } })
@Android({ language: 'c++', implementation: { include: '"scene/HybridIndirectLight.hpp"', className: 'HybridIndirectLight' } })
export declare class IndirectLight extends HybridObject {}
