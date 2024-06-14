// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/04/2024.
// Copyright (c)

#include <format>
#include <iostream>

#include <SFML/Graphics/Vertex.hpp>
#include <glm/vec2.hpp>

#include "silver/canvas.h"

namespace silver {
Canvas::Canvas(Window* target) : target_(target) {
  auto window_size = target_->window_.getSize();
  background_.create(window_size.x, window_size.y);
}

void Canvas::DrawPoint(const glm::vec2& point) {
  std::cout << std::format("{} {}", point.x, point.y) << std::endl;
  auto vertex = sf::Vertex(sf::Vector2f{point.x, point.y}, sf::Color::White);
  target_->window_.draw(&vertex, 1, sf::Points);
}

}  // namespace silver