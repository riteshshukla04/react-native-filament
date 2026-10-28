import { Android, Apple, type HybridObject } from 'react-native-nitro-modules'

export * from '#nitro/AssetIO'

/**
 * Reads asset bytes natively: memory-maps files and bundled assets, downloads URLs to a file first.
 * Internal to react-native-filament.
 */
@Apple({ language: 'swift', implementation: { className: 'HybridAssetIO' } })
@Android({ language: 'kotlin', implementation: { className: 'HybridAssetIO' } })
export declare class AssetIO extends HybridObject {
  public constructor()
  read(uri: string): Promise<ArrayBuffer>
  /** Absolute path of a directory the app can write temporary files to. */
  readonly temporaryDirectory: string
}
