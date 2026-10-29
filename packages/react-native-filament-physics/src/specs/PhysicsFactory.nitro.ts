import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'
import type { Engine } from 'react-native-filament'
import type { PhysicsWorldOptions } from '../types/PhysicsWorldOptions'
import type { PhysicsWorld } from './PhysicsWorld.nitro'

export * from '#nitro/PhysicsFactory'

/** Creates Bullet physics worlds, exported as `Physics`. */
@Apple({ language: 'c++', implementation: { include: '"HybridPhysicsFactory.hpp"', className: 'HybridPhysicsFactory' } })
@Android({ language: 'c++', implementation: { include: '"HybridPhysicsFactory.hpp"', className: 'HybridPhysicsFactory' } })
export declare class PhysicsFactory extends HybridObject {
  public constructor()
  /**
   * A Bullet physics world simulated on the render thread of `engine`, an Engine of react-native-filament.
   * @thread render
   */
  createWorld(engine: Engine, options: PhysicsWorldOptions): PhysicsWorld
}
