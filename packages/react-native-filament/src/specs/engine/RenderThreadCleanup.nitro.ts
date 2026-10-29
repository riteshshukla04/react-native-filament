import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'

export * from '#nitro/RenderThreadCleanup'

/** A function kept on the runtime that created it, such as a render-thread effect cleanup. */
@Apple({ language: 'c++', implementation: { include: '"engine/HybridRenderThreadCleanup.hpp"', className: 'HybridRenderThreadCleanup' } })
@Android({ language: 'c++', implementation: { include: '"engine/HybridRenderThreadCleanup.hpp"', className: 'HybridRenderThreadCleanup' } })
export declare class RenderThreadCleanup extends HybridObject {
  /**
   * Calls the function once, on the runtime that created it, after the work already queued there.
   * Later calls and calls after `dispose()` do nothing.
   * @thread any
   */
  run(): void
}
