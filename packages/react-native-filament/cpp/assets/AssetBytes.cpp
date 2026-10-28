#include "AssetBytes.hpp"

#include "platform/HybridPlatformServices.hpp"
#include "utils/PlatformErrors.hpp"

#include <stdexcept>

namespace margelo::nitro::filament {

std::string temporaryDirectory() {
  return HybridPlatformServices::getAssetIO().getTemporaryDirectory();
}

Promise<ArrayBuffer> readAssetBytes(const AssetSource& source) {
  if (const auto* buffer = std::get_if<ArrayBuffer>(&source)) {
    if (buffer->size() == 0) {
      throw std::invalid_argument("The ArrayBuffer source is empty.");
    }
    return Promise<ArrayBuffer>::resolved(ArrayBuffer::copy(*buffer));
  }
  auto bytes = Promise<ArrayBuffer>::pending();
  Promise<ArrayBuffer> read = HybridPlatformServices::getAssetIO().read(std::get<AssetUri>(source).uri);
  read.addOnResolvedListener([bytes](const ArrayBuffer& data) { bytes.resolve(ArrayBuffer(data)); });
  read.addOnRejectedListener([bytes](const std::exception_ptr& error) { bytes.reject(toPortableError(error)); });
  return bytes;
}

} // namespace margelo::nitro::filament
