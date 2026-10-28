#pragma once

#include "ContactChange.hpp"

#include <worklets/WorkletRuntime/WorkletRuntime.h>

#include <atomic>
#include <functional>
#include <memory>
#include <vector>

namespace margelo::nitro::filament {

class CollisionListeners final {
public:
  using Listener = std::function<bool(const std::vector<ContactChange>&)>;

  struct Entry {
    explicit Entry(Listener callback) : callback(std::move(callback)) {}

    Listener callback;
    std::atomic<bool> removed{false};
  };

  std::shared_ptr<Entry> add(Listener callback);
  bool empty();
  void dispatch(const std::vector<ContactChange>& changes, const worklets::WorkletRuntime& runtime);
  void clear();

private:
  std::vector<std::shared_ptr<Entry>> entries_;
};

} // namespace margelo::nitro::filament
