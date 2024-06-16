// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/29/2024.
// Copyright (c)
#pragma once

#include <vector>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <glm/vec2.hpp>

#include "silver/i_node.h"
#include "silver/window.h"

namespace silver {
class Canvas : public INode {
 public:
  Canvas(Window* target);

  void AddPoint(const glm::vec2& point);

  void Draw();

  void Clear();

  void OnUpdate(float delta_time) override;

 private:
  Window* target_;
  sf::RenderTexture background_;
  std::vector<sf::Vertex> points_;
};
}  // namespace silver