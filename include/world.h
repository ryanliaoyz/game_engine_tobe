#pragma once

#include "component_store.h"
#include "entity.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace tobe {
class World {
private:
  Entity next_entity = null_entity;
  std::unordered_set<Entity> alive;
  std::unordered_map<std::type_index, std::unique_ptr<IComponentStore>> stores;

  // Creates storage for component type T on first use.
  // Use only when the operation intentionally changes world structure.
  template <typename T> ComponentStore<T> &get_or_create_store() {
    auto idx = std::type_index(typeid(T));
    auto [it, _] =
        stores.try_emplace(idx, std::make_unique<ComponentStore<T>>());
    return *static_cast<ComponentStore<T> *>(it->second.get());
  }

  // Finds existing mutable storage for T without creating it.
  template <typename T> ComponentStore<T> *find_store() {
    auto idx = std::type_index(typeid(T));
    auto it = stores.find(idx);
    if (it == stores.end())
      return nullptr;
    return static_cast<ComponentStore<T> *>(it->second.get());
  }

  // Finds existing read-only storage for T without creating it.
  template <typename T> const ComponentStore<T> *find_store() const {
    auto idx = std::type_index(typeid(T));
    auto it = stores.find(idx);
    if (it == stores.end())
      return nullptr;
    return static_cast<const ComponentStore<T> *>(it->second.get());
  }

public:
  // Creates a new live entity. Entity 0 is reserved as null_entity.
  Entity create_entity() {
    alive.insert(++next_entity);
    return next_entity;
  }

  // Checks whether the handle currently refers to a live entity.
  bool is_alive(Entity entity) const {
    return entity != null_entity && alive.contains(entity);
  }

  // Destroys a live entity and removes all of its components.
  // Invalid or already-destroyed entities are ignored.
  void destroy_entity(Entity entity) {
    if (!is_alive(entity))
      return;
    alive.erase(entity);
    for (auto &[_, store] : stores) {
      store->remove(entity);
    }
  }

  // Adds or replaces component T on a live entity.
  // Invalid entities are ignored.
  template <typename T> void add_component(Entity entity, T component) {
    if (!is_alive(entity))
      return;
    get_or_create_store<T>().add(entity, std::move(component));
  }

  // Returns mutable component T if present; otherwise nullptr.
  // Does not create component storage.
  template <typename T> T *get_component(Entity entity) {
    auto *store = find_store<T>();
    return store ? store->get(entity) : nullptr;
  }

  // Returns read-only component T if present; otherwise nullptr.
  // Does not create component storage.
  template <typename T> const T *get_component(Entity entity) const {
    auto *store = find_store<T>();
    return store ? store->get(entity) : nullptr;
  }

  // Checks whether an entity has component T without creating storage.
  template <typename T> bool has_component(Entity entity) const {
    auto *store = find_store<T>();
    return store && store->has(entity);
  }

  // Removes component T if both the store and component exist.
  template <typename T> bool remove_component(Entity entity) {
    auto *store = find_store<T>();
    return store ? store->remove(entity) : false;
  }

  // Returns all live entities that contain every requested component type.
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
