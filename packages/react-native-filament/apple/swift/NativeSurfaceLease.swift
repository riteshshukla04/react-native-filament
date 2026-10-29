import NitroModules
import QuartzCore

final class NativeSurfaceLease: @unchecked Sendable {
  private let contentScale: Double
  private let transparent: Bool
  private let lock = NSLock()
  private var layer: CAMetalLayer?
  private var pixelSize: CGSize

  init(layer: CAMetalLayer, pixelSize: CGSize, contentScale: Double, transparent: Bool) {
    self.contentScale = contentScale
    self.layer = layer
    self.pixelSize = pixelSize
    self.transparent = transparent
  }

  func update(pixelSize: CGSize) -> Bool {
    lock.lock()
    defer { lock.unlock() }
    guard self.pixelSize != pixelSize else { return false }
    self.pixelSize = pixelSize
    return true
  }

  func toNativeSurface() -> NativeSurface {
    lock.lock()
    defer { lock.unlock() }
    let handle = layer.map { UInt64(UInt(bitPattern: Unmanaged.passUnretained($0).toOpaque())) } ?? 0
    return NativeSurface(
      handle: handle,
      width: Double(pixelSize.width),
      height: Double(pixelSize.height),
      contentScale: contentScale,
      transparent: transparent,
      synchronousTeardown: false,
      isReleased: .native { [self] in isReleased },
      release: .native { [self] in release() })
  }

  private var isReleased: Bool {
    lock.lock()
    defer { lock.unlock() }
    return layer == nil
  }

  private func release() {
    lock.lock()
    defer { lock.unlock() }
    layer = nil
  }
}
