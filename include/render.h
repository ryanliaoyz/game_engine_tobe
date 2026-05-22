#pragma once

#include "world.h"
namespace tobe {
struct Renderer {
  Renderer();
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  ~Renderer();

  bool should_close();
};
} // namespace tobe

namespace tobe::render {
void update(World &world);
}
