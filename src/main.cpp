#include "components.h"
#include "movement.h"
#include "render.h"
#include "world.h"

int main() {
  tobe::World world;

  auto e1 = world.create_entity();
  world.add_component<tobe::Position>(e1, {100.0f, 100.0f});
  world.add_component<tobe::Velocity>(e1, {30.0f, 20.0f});

  auto e2 = world.create_entity();
  world.add_component<tobe::Position>(e2, {400.0f, 225.0f});
  // e2 has no velocity — should sit still

  tobe::Renderer renderer;

  while (!renderer.should_close()) {
    tobe::movement::update(world, 1.0f / 60.0f);
    tobe::render::update(world);
  }

  return 0;
}
