import { Image } from 'react-native'

export function bundledAsset(asset: number): { uri: string } {
  const resolved = Image.resolveAssetSource(asset)
  if (resolved == null) throw new Error(`Asset ${asset} is not registered with the bundler.`)
  return { uri: resolved.uri }
}
