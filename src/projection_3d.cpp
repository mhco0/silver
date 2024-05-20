// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)

#include <glm/gtc/epsilon.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "silver/projection_3d.h"

namespace silver {
Projection3D::Projection3D(int space_width, int space_height, double fov,
                           double z_far, double z_near)
    : space_width_(space_width), space_height_(space_height) {
  double aspect_ratio = space_height / (space_width * 1.0);
  double scale_factor = 1.0 / glm::tan(glm::radians(fov / 2.0));
  double z_factor = z_far / (z_far - z_near);
  projection_matrix_ = glm::mat4x4{
      glm::vec4{aspect_ratio * scale_factor, 0, 0, 0},
      glm::vec4{0, scale_factor, 0, 0},
      glm::vec4{0, 0, z_factor, -z_far * z_factor},
      glm::vec4{0, 0, 1, 0},
  };
}

glm::vec2 Projection3D::Project(const glm::vec3& vec) {
  glm::vec4 extended_vector = {vec.x, vec.y, vec.z, 1};
  glm::vec4 result = extended_vector * projection_matrix_;
  if (glm::epsilonNotEqual(static_cast<double>(result.w), 0.0, 1e-6)) {
    result /= result.w;
  }
  result.x *= space_width_;
  result.y *= space_height_;

  return glm::vec2(result.x, result.y);
}
}  // namespace silver