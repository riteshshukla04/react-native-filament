import type { UInt64 } from 'react-native-nitro-modules'

/**
 * One OS surface handed to Filament: an `ANativeWindow` on Android, a `CAMetalLayer` on iOS.
 * Internal to react-native-filament.
 */
export interface NativeSurface {
  /** The native window or layer, which also identifies this surface. */
  handle: UInt64
  width: number
  height: number
  /** Pixels per point. */
  contentScale: number
  /** Composites with the views behind it. */
  transparent: boolean
  /** The OS destroys this surface once its destroyed callback returns, so teardown must finish first. */
  synchronousTeardown: boolean
  isReleased: () => boolean
  release: () => void
}
