// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 09/12/2024.
// Copyright (c)

#pragma once

#include <vector>

#include <glm/vec3.hpp>

#include "silver/triangle.h"

namespace silver {

struct VerticeData {
  glm::vec3 vertice{};
  glm::vec3 vertice_normal{};
};

class Object3d {
 public:
  Object3d(const std::vector<Triangle>& triangles);

  const std::vector<VerticeData>& Vertices() const;
  const std::vector<Triangle>& Triangles() const;

 private:
  std::vector<VerticeData> vertices_data_;
  std::vector<Triangle> triangle_data_;
};
}  // namespace silver