// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/29/2024.
// Copyright (c)
#pragma once

#include <array>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "silver/i_node.h"
#include "silver/object_3d.h"
#include "silver/projection_3d.h"
#include "silver/triangle.h"
#include "silver/window.h"

namespace silver {
class Canvas : public INode {
 public:
  Canvas(Window* target, Projection3d* projection);

  void AddObject(const Object3d& object);

  void DrawPoint(const glm::vec2& point, const sf::Color& color);
  void DrawPoints(const std::vector<glm::vec2>& points, const sf::Color& color);
  void DrawPoints(const std::vector<glm::vec2>& points,
                  const std::vector<sf::Color>& colors);
  void Draw();
  void FillTriangle(Triangle& triangle);

  void Clear();

  void OnUpdate(float delta_time) override;

 private:
  Window* target_;
  Projection3d* projection_;
  std::vector<Object3d> objects_;
};
}  // namespace silver