import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { MaterialInstance } from './MaterialInstance.nitro'

export * from '#nitro/Material'

/** A compiled material (`.filamat`, from Filament's `matc` of the same version). */
@Apple({ language: 'c++', implementation: { include: '"materials/HybridMaterial.hpp"', className: 'HybridMaterial' } })
@Android({ language: 'c++', implementation: { include: '"materials/HybridMaterial.hpp"', className: 'HybridMaterial' } })
export declare class Material extends HybridObject {
  /** @thread any */
  readonly materialName: string
  /** @thread any */
  readonly parameterNames: string[]
  /**
   * The instance shared by every renderable that uses the material without its own instance.
   * @thread render
   */
  readonly defaultInstance: MaterialInstance
  /** @thread render */
  createInstance(): MaterialInstance
}
