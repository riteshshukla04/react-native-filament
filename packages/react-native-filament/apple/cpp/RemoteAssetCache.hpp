#pragma once

#include <NitroModules/Promise.hpp>

#include <mutex>
#include <string>
#include <unordered_map>

namespace margelo::nitro::filament {

/** Downloads each URL once into the caches directory and resolves with the local file. */
class RemoteAssetCache final {
public:
  static RemoteAssetCache& shared();

  Promise<std::string> file(const std::string& requested);

private:
  void forget(const std::string& url);

  std::mutex mutex_;
  std::unordered_map<std::string, Promise<std::string>> downloads_;
};

} // namespace margelo::nitro::filament
