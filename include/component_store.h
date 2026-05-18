#pragma once

#include "entity.h"
#include <unordered_map>

namespace tobe {
class IComponentStore {
public:
  virtual ~IComponentStore() = default;
};

template <typename T> class ComponentStore : public IComponentStore {
  std::unordered_map<Entity, T> data;

public:
  void add(Entity e, T component) { data.emplace(e, std::move(component)); }
  T *get(Entity e) {
    auto it = data.find(e);
    return it == data.end() ? nullptr : &(it->second);
  }
  // const overload
  const T *get(Entity e) const {
    auto it = data.find(e);
    return it == data.end() ? nullptr : &(it->second);
  }
  bool has(Entity e) const { return data.contains(e); }

  bool remove(Entity e) { return data.erase(e); }
};
} // namespace tobe
