// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/29/2024.
// Copyright (c)
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <glm/vec2.hpp>

#include "silver/window.h"

namespace silver {
class Canvas {
 public:
  Canvas(Window* target);

  void DrawPoint(const glm::vec2& point);

 private:
  Window* target_;
  sf::RenderTexture background_;
};
}  // namespace silver