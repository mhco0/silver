// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/22/2024.
// Copyright (c)
#pragma once

#include <glm/vec3.hpp>

#include "silver/projection_3d.h"

namespace silver {

class CameraControllerWidget;

class Camera3d {
 public:
  explicit Camera3d() {
    normal_ = {};
    focus_ = {};
    forward_ = {};
    distance_from_projection_ = 0.0;
    camera_height_ = 30;
    camera_width_ = 20;
  }

 protected:
  glm::vec3 normal_;
  glm::vec3 focus_;
  glm::vec3 forward_;
  double distance_from_projection_;
  int camera_height_;
  int camera_width_;
  friend class CameraControllerWidget;
};

}  // namespace silver