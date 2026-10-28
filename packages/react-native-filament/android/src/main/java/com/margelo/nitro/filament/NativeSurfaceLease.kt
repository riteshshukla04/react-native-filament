package com.margelo.nitro.filament

import android.util.Size
import android.view.Surface
import com.margelo.nitro.core.Callback
import java.util.concurrent.CountDownLatch
import java.util.concurrent.atomic.AtomicBoolean

class NativeSurfaceLease private constructor(
  private val window: Long,
  @Volatile private var size: Size,
  private val contentScale: Double,
  private val transparent: Boolean,
  val synchronousTeardown: Boolean,
  private val onReleased: (NativeSurfaceLease) -> Unit,
) {
  private val released = AtomicBoolean(false)
  private val releaseFinished = CountDownLatch(1)

  fun resize(size: Size) {
    this.size = size
  }

  fun awaitRelease() {
    releaseFinished.await()
  }

  fun release() {
    if (released.compareAndSet(false, true)) {
      NativeWindow.release(window)
      onReleased(this)
      releaseFinished.countDown()
    }
  }

  fun toNativeSurface(): NativeSurface = NativeSurface(
    handle = window.toULong(),
    width = size.width.toDouble(),
    height = size.height.toDouble(),
    contentScale = contentScale,
    transparent = transparent,
    synchronousTeardown = synchronousTeardown,
    isReleased = Callback.Arity0 { released.get() },
    release = Callback.Arity0 { release() },
  )

  companion object {
    fun acquire(
      surface: Surface,
      size: Size,
      contentScale: Double,
      transparent: Boolean,
      synchronousTeardown: Boolean,
      onReleased: (NativeSurfaceLease) -> Unit,
    ): NativeSurfaceLease? {
      val window = NativeWindow.acquire(surface)
      if (window == 0L) return null
      return NativeSurfaceLease(window, size, contentScale, transparent, synchronousTeardown, onReleased)
    }
  }
}
