// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)
#pragma once

#include <optional>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "silver/camera_3d.h"
#include "silver/window.h"

namespace silver {

class Projection3d {
 public:
  Projection3d(Camera3d* camera, Window* window);

  std::optional<glm::vec2> Project(const glm::vec3& vec);

 private:
  Camera3d* camera_;
  Window* window_;
};
}  // namespace silver