#include "render.h"
#include "components.h"
#include "raylib.h"

namespace tobe {
Renderer::Renderer() {
  InitWindow(800, 450, "tobe");
  SetTargetFPS(60);
}

Renderer::~Renderer() { CloseWindow(); }
bool Renderer::should_close() { return WindowShouldClose(); }
void render::update(World &world) {
  BeginDrawing();
  ClearBackground(BLACK);

  for (auto e : world.view<Position>()) {
    auto *pos = world.get_component<Position>(e);
    DrawCircle(static_cast<int>(pos->x), static_cast<int>(pos->y), 10.0f, RED);
  }

  EndDrawing();
}
} // namespace tobe
