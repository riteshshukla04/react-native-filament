import { describe, expect, it } from 'react-native-harness'
import { Platform } from 'react-native'
import { Engine, Filament } from 'react-native-filament'
import pin from 'react-native-filament/filament.json'

describe('FilamentFactory', () => {
  it('reports the version of the linked Filament binaries', () => {
    expect(Filament.filamentVersion).toBe(pin.version)
  })

  it('lists the backends of this platform, preferred first', () => {
    const backends = Filament.supportedBackends
    if (Platform.OS === 'ios') {
      expect(backends).toEqual(['metal'])
    } else {
      expect(backends).toEqual(backends.includes('vulkan') ? ['vulkan', 'opengl'] : ['opengl'])
    }
  })

  it('creates Engines that are instances of the Engine class', async () => {
    const engine = await Filament.createEngine({})
    expect(engine).toBeInstanceOf(Engine)
    await engine.shutdown()
  })
})
