// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 09/12/2024.
// Copyright (c)

#include "silver/object_3d.h"

#include <utility>
#include <vector>

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include "silver/triangle.h"

namespace silver {

Object3d::Object3d(const std::vector<Triangle>& triangles) {
  for (const auto& triangle : triangles) {
    triangle_data_.emplace_back(triangle);
    int max_idx =
        std::max(triangle.vertices_idx.x,
                 std::max(triangle.vertices_idx.y, triangle.vertices_idx.z));

    if (vertices_data_.size() <= max_idx) {
      vertices_data_.resize(max_idx + 1);
    }

    vertices_data_.at(triangle.vertices_idx.x).vertice = triangle.vertices[0];
    vertices_data_.at(triangle.vertices_idx.y).vertice = triangle.vertices[1];
    vertices_data_.at(triangle.vertices_idx.z).vertice = triangle.vertices[2];
  }

  for (const auto& triangle : triangle_data_) {
    vertices_data_.at(triangle.vertices_idx.x).vertice_normal +=
        triangle.normal;
    vertices_data_.at(triangle.vertices_idx.y).vertice_normal +=
        triangle.normal;
    vertices_data_.at(triangle.vertices_idx.z).vertice_normal +=
        triangle.normal;
  }

  for (auto& vertice : vertices_data_) {
    vertice.vertice_normal = glm::normalize(vertice.vertice_normal);
  }
}

const std::vector<VerticeData>& Object3d::Vertices() const {
  return vertices_data_;
}

const std::vector<Triangle>& Object3d::Triangles() const {
  return triangle_data_;
}

}  // namespace silver