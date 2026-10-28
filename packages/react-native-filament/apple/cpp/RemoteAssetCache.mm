#include "RemoteAssetCache.hpp"

#import <CommonCrypto/CommonDigest.h>
#import <Foundation/Foundation.h>

#include <stdexcept>

namespace margelo::nitro::filament {

namespace {

  NSString* cacheName(const std::string& url) {
    unsigned char digest[CC_SHA256_DIGEST_LENGTH];
    CC_SHA256(url.data(), static_cast<CC_LONG>(url.size()), digest);
    NSMutableString* name = [NSMutableString stringWithCapacity:CC_SHA256_DIGEST_LENGTH * 2];
    for (unsigned char byte : digest) {
      [name appendFormat:@"%02x", byte];
    }
    return name;
  }

  NSURL* moveIntoCache(NSURL* temporary, const std::string& url) {
    NSFileManager* files = NSFileManager.defaultManager;
    NSError* error = nil;
    NSURL* caches = [files URLForDirectory:NSCachesDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:YES error:&error];
    NSURL* directory = [caches URLByAppendingPathComponent:@"react-native-filament" isDirectory:YES];
    if (caches == nil || ![files createDirectoryAtURL:directory withIntermediateDirectories:YES attributes:nil error:&error]) {
      throw std::runtime_error(std::string(error.localizedDescription.UTF8String));
    }
    NSURL* target = [directory URLByAppendingPathComponent:cacheName(url)];
    [files removeItemAtURL:target error:nil];
    if (![files moveItemAtURL:temporary toURL:target error:&error]) {
      throw std::runtime_error(std::string(error.localizedDescription.UTF8String));
    }
    return target;
  }

} // namespace

RemoteAssetCache& RemoteAssetCache::shared() {
  static RemoteAssetCache cache;
  return cache;
}

Promise<std::string> RemoteAssetCache::file(const std::string& requested) {
  std::string url = requested;
  std::unique_lock lock(mutex_);
  if (auto found = downloads_.find(url); found != downloads_.end()) {
    return found->second;
  }
  auto promise = Promise<std::string>::pending();
  downloads_.emplace(url, promise);
  lock.unlock();
  NSURL* remote = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
  NSURLSessionDownloadTask* task = [NSURLSession.sharedSession
      downloadTaskWithURL:remote
        completionHandler:^(NSURL* temporary, NSURLResponse* response, NSError* error) {
          try {
            if (error != nil) {
              throw std::runtime_error("Downloading " + url + " failed: " + std::string(error.localizedDescription.UTF8String));
            }
            if ([response isKindOfClass:NSHTTPURLResponse.class]) {
              NSInteger status = static_cast<NSHTTPURLResponse*>(response).statusCode;
              if (status < 200 || status >= 300) {
                throw std::runtime_error("Downloading " + url + " failed with HTTP " + std::to_string(status) + ".");
              }
            }
            promise.resolve(std::string(moveIntoCache(temporary, url).path.UTF8String));
          } catch (...) {
            forget(url);
            promise.reject(std::current_exception());
          }
        }];
  [task resume];
  return promise;
}

void RemoteAssetCache::forget(const std::string& url) {
  std::unique_lock lock(mutex_);
  downloads_.erase(url);
}

} // namespace margelo::nitro::filament
