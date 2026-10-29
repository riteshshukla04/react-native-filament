import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { Entity } from '../types/Entity'

export * from '#nitro/Renderable'

/**
 * Geometry created and owned by RNF. `dispose()` removes it from every scene and destroys its
 * entity and buffers; the renderable keeps its material instance alive until then. It is also
 * destroyed when its JS object is garbage collected, so keep a reference while it is shown.
 */
@Apple({ language: 'c++', implementation: { include: '"geometry/HybridRenderable.hpp"', className: 'HybridRenderable' } })
@Android({ language: 'c++', implementation: { include: '"geometry/HybridRenderable.hpp"', className: 'HybridRenderable' } })
export declare class Renderable extends HybridObject {
  /** @thread any */
  readonly entity: Entity
}
