// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/16/2024.
// Copyright (c)

#include <format>
#include <iostream>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

#include "silver/camera_3d.h"

namespace silver {
Camera3d::Camera3d() {
  Reset();
}

glm::vec3 Camera3d::Translate(const glm::vec3& point) {
  glm::mat3x3 basis_ = {
      glm::vec3{u_.x, v_.x, n_.x},
      glm::vec3{u_.y, v_.y, n_.y},
      glm::vec3{u_.z, v_.z, n_.z},
  };

  return basis_ * (point - focus_);
}

void Camera3d::Reset() {
  u_ = glm::vec3{1.0, 0.0, 0.0};
  v_ = glm::vec3{0.0, 1.0, 0.0};
  n_ = glm::vec3{0.0, 0.0, 1.0};
  focus_ = glm::vec3{0.0f, 0.0f, -1.0f};
  distance_from_projection_ = 1.0f;
  visible_area_ = glm::vec2{1.0f, 1.0f};
  Orthonomalize();
}

void Camera3d::Orthonomalize() {
  n_ = glm::normalize(n_);
  v_ = glm::normalize(v_);
  v_ = v_ - n_ * (glm::dot(v_, n_));
  u_ = glm::cross(v_, n_);
}

}  // namespace silver