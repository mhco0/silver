// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/29/2024.
// Copyright (c)
#pragma once

#include <array>
#include <vector>

#include <SFML/Graphics/Vertex.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "silver/i_node.h"
#include "silver/projection_3d.h"
#include "silver/window.h"

namespace silver {
class Canvas : public INode {
 public:
  Canvas(Window* target, Projection3d* projection);

  void AddObject(const std::vector<glm::vec3>& object);

  void DrawPoint(const glm::vec2& point);
  void Draw();
  void FillTriangle(std::array<glm::vec2, 3>& triangle);

  void Clear();

  void OnUpdate(float delta_time) override;

 private:
  Window* target_;
  Projection3d* projection_;
  std::vector<std::vector<glm::vec3>> objects_;
};
}  // namespace silver