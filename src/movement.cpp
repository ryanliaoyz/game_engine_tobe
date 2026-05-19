#include "movement.h"
#include "components.h"

void tobe::movement::update(World &world, float dt) {
  for (auto e : world.view<Position, Velocity>()) {
    auto *pos = world.get_component<Position>(e);
    auto *vel = world.get_component<Velocity>(e);
    pos->x += vel->dx * dt;
    pos->y += vel->dy * dt;
  }
}
