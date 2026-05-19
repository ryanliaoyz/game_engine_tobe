#pragma once

#include "component_store.h"
#include "entity.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace tobe {
class World {
private:
  Entity next_entity = 0;
  std::unordered_set<Entity> alive;
  std::unordered_map<std::type_index, std::unique_ptr<IComponentStore>> stores;

  template <typename T> ComponentStore<T> &get_store() {
    auto idx = std::type_index(typeid(T));
    auto [it, _] =
        stores.try_emplace(idx, std::make_unique<ComponentStore<T>>());
    return *static_cast<ComponentStore<T> *>(it->second.get());
  }

  template <typename T> const ComponentStore<T> *get_store() const {
    auto idx = std::type_index(typeid(T));
    auto it = stores.find(idx);
    if (it == stores.end())
      return nullptr;
    return static_cast<const ComponentStore<T> *>(it->second.get());
  }

public:
  Entity create_entity() {
    alive.insert(++next_entity);
    return next_entity;
  }
  void destroy_entity(Entity entity) {
    alive.erase(entity);
    for (auto &[type, store] : stores) {
      store->remove(entity);
    }
  }

  template <typename T> void add_component(Entity entity, T component) {
    get_store<T>().add(entity, std::move(component));
  }

  template <typename T> T *get_component(Entity entity) {
    return get_store<T>().get(entity);
  }

  template <typename T> const T *get_component(Entity entity) const {
    auto *store = get_store<T>();
    return store ? store->get(entity) : nullptr;
  }

  template <typename T> bool has_component(Entity entity) const {
    auto *store = get_store<T>();
    return store && store->has(entity);
  }

  template <typename T> bool remove_component(Entity entity) {
    return get_store<T>().remove(entity);
  }

  template <typename... Ts> std::vector<Entity> view() const {
    std::vector<Entity> ret;
    for (auto &entity : alive) {
      if ((has_component<Ts>(entity) && ...))
        ret.push_back(entity);
    }
    return ret;
  }
};
} // namespace tobe
