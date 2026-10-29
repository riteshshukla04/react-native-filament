import NitroModules
import UIKit

/** Fabric creates the view and sets its props on the main thread, which owns every member but `setSurfaceObserver`. */
final class HybridFilamentView: HybridFilamentViewSpec_base, HybridFilamentViewSpec_protocol, @unchecked Sendable {
  let view: MetalView

  private var observer: SurfaceObserver?
  private var surface: NativeSurfaceLease?

  var transparent: Bool? {
    didSet {
      guard oldValue != transparent else { return }
      MainActor.assumeIsolated {
        applyTransparency()
        replaceSurface()
      }
    }
  }

  override init() throws {
    view = MainActor.assumeIsolated { MetalView() }
    try super.init()
    MainActor.assumeIsolated {
      applyTransparency()
      view.onSurfaceChange = { [weak self] in self?.updateSurface() }
    }
  }

  func setSurfaceObserver(observer: SurfaceObserver?) throws {
    DispatchQueue.main.async { [weak self] in
      guard let self else { return }
      self.surface = nil
      self.observer = observer
      self.updateSurface()
    }
  }

  private var isTransparent: Bool { transparent ?? false }

  @MainActor private var contentScale: CGFloat {
    view.window?.screen.scale ?? UIScreen.main.scale
  }

  @MainActor private var pixelSize: CGSize {
    CGSize(width: view.bounds.width * contentScale, height: view.bounds.height * contentScale)
  }

  @MainActor private func applyTransparency() {
    view.isOpaque = !isTransparent
    view.metalLayer.isOpaque = !isTransparent
    view.backgroundColor = isTransparent ? .clear : .black
  }

  @MainActor private func replaceSurface() {
    guard let observer, let surface else { return }
    self.surface = nil
    try? observer.onDestroyed.callSync(surface.toNativeSurface())
    updateSurface()
  }

  @MainActor private func updateSurface() {
    let size = pixelSize
    view.metalLayer.drawableSize = size
    guard let observer else { return }
    let isVisible = view.window != nil && size.width > 0 && size.height > 0
    if isVisible, let surface {
      if surface.update(pixelSize: size) {
        try? observer.onResized.callSync(surface.toNativeSurface())
      }
    } else if isVisible {
      let created = NativeSurfaceLease(
        layer: view.metalLayer, pixelSize: size, contentScale: Double(contentScale), transparent: isTransparent)
      surface = created
      try? observer.onCreated.callSync(created.toNativeSurface())
    } else if let surface {
      self.surface = nil
      try? observer.onDestroyed.callSync(surface.toNativeSurface())
    }
  }
}
