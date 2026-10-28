import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { EngineBackend } from './types/EngineBackend'
import type { EngineOptions } from './types/EngineOptions'
import type { Engine } from './engine/Engine.nitro'

export * from '#nitro/FilamentFactory'

/**
 * The root of the native API, exported as `Filament`. Reports the linked Filament version and the
 * backends this device supports, and creates Engines. Engines of one factory reuse each other's render
 * worklet runtimes, so the factory lives as long as its JS runtime.
 */
@Apple({ language: 'c++', implementation: { include: '"engine/HybridFilamentFactory.hpp"', className: 'HybridFilamentFactory' } })
@Android({ language: 'c++', implementation: { include: '"engine/HybridFilamentFactory.hpp"', className: 'HybridFilamentFactory' } })
export declare class FilamentFactory extends HybridObject {
  public constructor()
  /**
   * Version of the linked Filament binaries, for example `"1.78.0"`.
   * @thread any
   */
  readonly filamentVersion: string
  /**
   * Backends this device can create an Engine with, preferred first.
   * @thread any
   */
  readonly supportedBackends: EngineBackend[]
  /**
   * Creates an Engine with its own render thread.
   * @thread any
   */
  createEngine(options: EngineOptions): Promise<Engine>
}
