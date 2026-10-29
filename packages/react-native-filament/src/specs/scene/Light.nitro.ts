import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { Entity } from '../types/Entity'
import type { LightType } from '../types/LightType'

export * from '#nitro/Light'

/**
 * A light entity created with `Engine.createDirectionalLight()`, `createSunLight()`,
 * `createPointLight()`, `createSpotLight()` or `createFocusedSpotLight()`. Change it through
 * `Engine.lightManager`.
 */
@Apple({ language: 'c++', implementation: { include: '"scene/HybridLight.hpp"', className: 'HybridLight' } })
@Android({ language: 'c++', implementation: { include: '"scene/HybridLight.hpp"', className: 'HybridLight' } })
export declare class Light extends HybridObject {
  /** @thread any */
  readonly entity: Entity
  /** @thread any */
  readonly type: LightType
}
