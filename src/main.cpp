#include "component_store.h"

struct Position {
  float x, y;
};

int main() {
  tobe::ComponentStore<Position> store;
  store.add(1, Position{3.0f, 4.0f});
  auto *p = store.get(1);
  bool h = store.has(1);
  store.remove(1);
  return 0;
}
