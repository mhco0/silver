// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/16/2024.
// Copyright (c)

#include <glm/geometric.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

#include "silver/camera_3d.h"

namespace silver {
Camera3d::Camera3d()
    : u_{0.0, 0.0, 1.0},
      v_{0.0, 1.0, 0.0},
      n_{1.0, 0.0, 0.0},
      basis_{
          glm::vec3{u_.x, v_.x, n_.x},
          glm::vec3{u_.y, v_.y, n_.y},
          glm::vec3{u_.z, v_.z, n_.z},
      },
      focus_{},
      distance_from_projection_{0.0},
      camera_height_{2.0},
      camera_width_{2.0} {}

glm::vec3 Camera3d::Translate(const glm::vec3& point) {
  return glm::vec3{basis_ * (point - focus_)};
}

void Camera3d::Reset() {
  u_ = glm::vec3{0.0, 0.0, 1.0};
  v_ = glm::vec3{0.0, 1.0, 0.0};
  n_ = glm::vec3{1.0, 0.0, 0.0};
  focus_ = glm::vec3{};
  distance_from_projection_ = 0.0f;
  camera_width_ = 2.0f;
  camera_height_ = 2.0f;
  Orthonomalize();
}

void Camera3d::Orthonomalize() {
  v_ -= (glm::dot(v_, n_) / glm::dot(n_, n_)) * n_;
  u_ = glm::cross(n_, v_);
  n_ = glm::normalize(n_);
  u_ = glm::normalize(u_);
  v_ = glm::normalize(v_);
  basis_ = {
      glm::vec3{u_.x, v_.x, n_.x},
      glm::vec3{u_.y, v_.y, n_.y},
      glm::vec3{u_.z, v_.z, n_.z},
  };
}

}  // namespace silver