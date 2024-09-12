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

struct TriangleData {
  glm::ivec3 vertice_idx{};
  glm::vec3 normal{};
};

class Object3d {
 public:
  Object3d(const std::vector<Triangle>& triangles);

 private:
  std::vector<VerticeData> vertices_data_;
  std::vector<TriangleData> triangle_data_;
};
}  // namespace silver