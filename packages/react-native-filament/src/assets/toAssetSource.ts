import { Image } from 'react-native'
import type { AssetSource } from '../specs/types/AssetSource'
import type { AssetLike } from './AssetLike'

export function toAssetSource(asset: AssetLike): AssetSource {
  if (typeof asset === 'number') {
    const resolved = Image.resolveAssetSource(asset)
    if (resolved == null) throw new Error(`Asset ${asset} is not registered with the bundler.`)
    return { uri: resolved.uri }
  }
  if (typeof asset === 'string') return { uri: asset }
  return asset
}
