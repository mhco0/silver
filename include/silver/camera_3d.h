// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/22/2024.
// Copyright (c)
#pragma once

#include <glm/vec3.hpp>

#include "silver/projection_3d.h"

namespace silver {

class CameraControllerWidget;

class Camera3d {
 public:
  explicit Camera3d();

  void Orthonomalize();

 protected:
  glm::vec3 focus_;
  glm::vec3 n_;
  glm::vec3 v_;
  glm::vec3 u_;
  float distance_from_projection_;
  float camera_height_;
  float camera_width_;
  friend class CameraControllerWidget;
};

}  // namespace silver