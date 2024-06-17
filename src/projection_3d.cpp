// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)

#include <glm/gtc/epsilon.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "silver/camera_3d.h"
#include "silver/projection_3d.h"
#include "silver/window.h"

namespace silver {
Projection3d::Projection3d(Camera3d* camera, Window* window)
    : camera_(camera), window_(window) {}

glm::vec2 Projection3d::Project(const glm::vec3& vec) {
  glm::vec3 camera_view = camera_->Translate(vec);
  if (glm::epsilonNotEqual(camera_view.z, 0.0f, 1e-6f)) {
    camera_view /= camera_view.z;
  }
  glm::vec3 projection_point = glm::vec3{
      camera_view.x * camera_->distance_from_projection_,
      camera_view.y * camera_->distance_from_projection_,
      camera_->distance_from_projection_,
  };
  projection_point.x /= camera_->visible_area_.x;
  projection_point.y /= camera_->visible_area_.y;

  auto window_size = window_->window_.getSize();

  return glm::vec2{((projection_point.x + 1) / 2) * window_size.x,
                   ((1 - projection_point.y) / 2) * window_size.y};
}
}  // namespace silver