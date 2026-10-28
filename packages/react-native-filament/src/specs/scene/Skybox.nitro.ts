import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'

export * from '#nitro/Skybox'

/**
 * A scene background of one color from `Engine.createSkybox()` or a KTX cubemap from
 * `Engine.loadSkybox()`. Apply it with `Scene.setSkybox()`.
 */
@Apple({ language: 'c++', implementation: { include: '"scene/HybridSkybox.hpp"', className: 'HybridSkybox' } })
@Android({ language: 'c++', implementation: { include: '"scene/HybridSkybox.hpp"', className: 'HybridSkybox' } })
export declare class Skybox extends HybridObject {}
