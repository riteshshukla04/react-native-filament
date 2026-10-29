const { getDefaultConfig, mergeConfig } = require('@react-native/metro-config')
const { drawableFileTypes } = require('@react-native/asset-utils')
const path = require('path')
const fs = require('fs')

// React Native 0.88 bundles .ktx files as Android drawables, which AGP rejects; keep them raw resources.
drawableFileTypes.delete('ktx')

const root = path.resolve(__dirname, '..', '..')
const defaultConfig = getDefaultConfig(__dirname)
const sharedAssetNames = new Set(fs.readdirSync(path.join(root, 'apps', 'shared', 'assets')))
const librarySources = {
  'react-native-filament': path.join(root, 'packages', 'react-native-filament', 'src', 'index.ts'),
  'react-native-filament-physics': path.join(root, 'packages', 'react-native-filament-physics', 'src', 'index.ts'),
}

/** @type {import('@react-native/metro-config').MetroConfig} */
const config = {
  watchFolders: [root],
  resolver: {
    assetExts: [...defaultConfig.resolver.assetExts, 'glb', 'ktx', 'filamat'],
    nodeModulesPaths: [path.join(root, 'node_modules')],
    // Shared assets are served from this app's `assets` symlink so their URLs stay under /assets/.
    resolveRequest: (context, moduleName, platform) => {
      if (librarySources[moduleName] != null) return { type: 'sourceFile', filePath: librarySources[moduleName] }
      const fileName = path.basename(moduleName)
      if (!sharedAssetNames.has(fileName)) return context.resolveRequest(context, moduleName, platform)
      return { type: 'assetFiles', filePaths: [path.join(__dirname, 'assets', fileName)] }
    },
  },
  transformer: {
    getTransformOptions: async () => ({
      transform: {
        experimentalImportSupport: false,
        inlineRequires: true,
      },
    }),
  },
}

module.exports = mergeConfig(defaultConfig, config)
