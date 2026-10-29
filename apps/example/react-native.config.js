// react-native-video mixes Swift and Objective-C sources, which React Native's SwiftPM autolinking cannot build.
module.exports = {
  dependencies: {
    'react-native-video': { platforms: { ios: null } },
  },
}
