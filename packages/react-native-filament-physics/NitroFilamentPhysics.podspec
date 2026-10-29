require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

# React Native CLI still discovers iOS dependencies through a podspec. Package.swift builds the sources.
Pod::Spec.new do |s|
  s.name         = "NitroFilamentPhysics"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]
  s.source       = { :git => "https://github.com/margelo/react-native-filament.git", :tag => "#{s.version}" }
  s.ios.deployment_target = "16.0"
end
