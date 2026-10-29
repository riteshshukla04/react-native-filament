#include "HybridAssetIO.hpp"

#include "RemoteAssetCache.hpp"

#import <Foundation/Foundation.h>

#include <stdexcept>
#include <string>

namespace margelo::nitro::filament {

namespace {

  NSURL* bundledResource(NSString* name) {
    for (NSBundle* bundle in @[ NSBundle.mainBundle, SWIFTPM_MODULE_BUNDLE ]) {
      NSURL* url = [bundle URLForResource:name.stringByDeletingPathExtension withExtension:name.pathExtension];
      if (url != nil) {
        return url;
      }
    }
    throw std::runtime_error("No asset named " + std::string(name.UTF8String) + " is bundled with the app.");
  }

  ArrayBuffer mapFile(NSURL* file) {
    NSError* error = nil;
    NSData* data = [NSData dataWithContentsOfURL:file options:NSDataReadingMappedAlways error:&error];
    if (data == nil) {
      throw std::runtime_error(std::string(error.localizedDescription.UTF8String));
    }
    if (data.length == 0) {
      throw std::runtime_error(std::string(file.path.UTF8String) + " is empty.");
    }
    return ArrayBuffer::wrap(static_cast<uint8_t*>(const_cast<void*>(data.bytes)), data.length, [data] { (void)data; });
  }

  void resolveMapped(Promise<ArrayBuffer> promise, NSURL* file) {
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
      try {
        promise.resolve(mapFile(file));
      } catch (...) {
        promise.reject(std::current_exception());
      }
    });
  }

} // namespace

std::string HybridAssetIO::getTemporaryDirectory() {
  return std::string(NSTemporaryDirectory().UTF8String);
}

Promise<ArrayBuffer> HybridAssetIO::read(const std::string& uri) {
  auto promise = Promise<ArrayBuffer>::pending();
  try {
    NSString* string = [NSString stringWithUTF8String:uri.c_str()];
    NSURL* url = [NSURL URLWithString:string];
    NSString* scheme = url.scheme;
    if (scheme == nil) {
      resolveMapped(promise, bundledResource(string));
    } else if ([scheme isEqualToString:@"file"]) {
      resolveMapped(promise, url);
    } else if ([scheme isEqualToString:@"http"] || [scheme isEqualToString:@"https"]) {
      Promise<std::string> download = RemoteAssetCache::shared().file(uri);
      download.addOnResolvedListener([promise](const std::string& path) {
        resolveMapped(promise, [NSURL fileURLWithPath:[NSString stringWithUTF8String:path.c_str()]]);
      });
      download.addOnRejectedListener([promise](const std::exception_ptr& error) { promise.reject(std::exception_ptr(error)); });
    } else {
      throw std::invalid_argument("Unsupported asset URI scheme '" + std::string(scheme.UTF8String) + "' in " + uri + ".");
    }
  } catch (...) {
    promise.reject(std::current_exception());
  }
  return promise;
}

} // namespace margelo::nitro::filament
