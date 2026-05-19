#pragma once

#include "entity.h"
#include <unordered_map>

namespace tobe {
class IComponentStore {
public:
  virtual bool remove(Entity e) = 0;
  virtual ~IComponentStore() = default;
};

template <typename T> class ComponentStore : public IComponentStore {
private:
  std::unordered_map<Entity, T> data;

public:
  void add(Entity e, T component) { data.insert_or_assign(e, std::move(component)); }

  T *get(Entity e) {
    auto it = data.find(e);
    return it == data.end() ? nullptr : &(it->second);
  }

  const T *get(Entity e) const {
    auto it = data.find(e);
    return it == data.end() ? nullptr : &(it->second);
  }

  bool has(Entity e) const { return data.contains(e); }

  bool remove(Entity e) override { return data.erase(e); }
};
} // namespace tobe
