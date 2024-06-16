// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/04/2024.
// Copyright (c)

#include <format>
#include <iostream>

#include <SFML/Graphics/Vertex.hpp>
#include <glm/vec2.hpp>

#include "silver/canvas.h"

namespace silver {
Canvas::Canvas(Window* target) : target_(target), points_{} {
  auto window_size = target_->window_.getSize();
  background_.create(window_size.x, window_size.y);
}

void Canvas::AddPoint(const glm::vec2& point) {
  std::cout << std::format("{} {}", point.x, point.y) << std::endl;
  points_.push_back(
      sf::Vertex(sf::Vector2f{point.x, point.y}, sf::Color::White));
}

void Canvas::Draw() {
  for (auto& point : points_) {
    target_->window_.draw(&point, 1, sf::Points);
  }
}

void Canvas::Clear() {
  points_.clear();
}

void Canvas::OnUpdate(float delta_time) {
  Draw();
}

}  // namespace silver