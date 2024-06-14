// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)
#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace silver {
class Projection3d {
 public:
  Projection3d(int space_width, int space_height, double fov, double z_far,
               double z_near);

  glm::vec2 Project(const glm::vec3& vec);

 private:
  int space_width_;
  int space_height_;
  glm::mat4x4 projection_matrix_;
};
}  // namespace silver