import { FilamentFactory } from './specs/FilamentFactory.nitro'

/**
 * The root of the native API: the linked Filament version, the backends this device supports, and
 * `createEngine()`.
 */
export const Filament = new FilamentFactory()
