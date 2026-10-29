import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'

export * from '#nitro/FrameListenerSubscription'

/**
 * Returned by `Engine.addOnFrameListener()`. Call `remove()` to stop the listener. Dropping it does
 * not remove the listener; it runs until `remove()` or Engine shutdown.
 */
@Apple({
  language: 'c++',
  implementation: { include: '"engine/HybridFrameListenerSubscription.hpp"', className: 'HybridFrameListenerSubscription' },
})
@Android({
  language: 'c++',
  implementation: { include: '"engine/HybridFrameListenerSubscription.hpp"', className: 'HybridFrameListenerSubscription' },
})
export declare class FrameListenerSubscription extends HybridObject {
  /**
   * Stops future calls. Idempotent. A frame already in progress may still call the listener once.
   * @thread any
   */
  remove(): void
}
