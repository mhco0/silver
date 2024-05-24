// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/22/2024.
// Copyright (c)
#pragma once

#include <glm/vec3.hpp>

#include "silver/projection_3d.h"

namespace silver {

class Camera3d {

 private:
  glm::vec3 normal_;
  glm::vec3 focus_;
  glm::vec3 foward_;
  double distance_from_projection_;
  int camera_height_;
  int camera_width_;
};

}  // namespace silver