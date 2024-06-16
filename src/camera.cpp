// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/16/2024.
// Copyright (c)

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include "silver/camera_3d.h"

namespace silver {
Camera3d::Camera3d()
    : v_{1.0},
      n_{1.0},
      u_{1.0},
      focus_{},
      distance_from_projection_{0.0},
      camera_height_{0.0},
      camera_width_{0.0} {}

void Camera3d::Orthonomalize() {
  v_ -= (glm::dot(v_, n_) / glm::dot(n_, n_)) * n_;
  u_ = glm::cross(n_, v_);
  n_ = glm::normalize(n_);
  u_ = glm::normalize(u_);
  v_ = glm::normalize(v_);
}

}  // namespace silver