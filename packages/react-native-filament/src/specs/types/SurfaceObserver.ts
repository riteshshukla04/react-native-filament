import type { NativeSurface } from './NativeSurface'

export interface SurfaceObserver {
  onCreated: (surface: NativeSurface) => void
  onResized: (surface: NativeSurface) => void
  onDestroyed: (surface: NativeSurface) => void
}
