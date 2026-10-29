import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'

export * from '#nitro/ValueBinding'

/** A number that any thread can write and render-thread code can read without waiting on another runtime. */
@Apple({ language: 'c++', implementation: { include: '"control/HybridValueBinding.hpp"', className: 'HybridValueBinding' } })
@Android({ language: 'c++', implementation: { include: '"control/HybridValueBinding.hpp"', className: 'HybridValueBinding' } })
export declare class ValueBinding extends HybridObject {
  /**
   * Stores the value and requests a frame.
   * @thread any
   */
  set(value: number): void
  /**
   * Latest value set.
   * @thread any
   */
  readonly value: number
}
