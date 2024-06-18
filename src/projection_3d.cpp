// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)

#include <format>
#include <iostream>
#include <optional>

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

std::optional<glm::vec2> Projection3d::Project(const glm::vec3& vec) {
  glm::vec3 camera_view = camera_->Translate(vec);
  glm::vec3 projection_point = glm::vec3{
      camera_view.x * camera_->distance_from_projection_ / camera_view.z,
      camera_view.y * camera_->distance_from_projection_ / camera_view.z,
      camera_->distance_from_projection_,
  };

  auto out_of_screen = [this](float x, float y) {
    return -camera_->visible_area_.x > x || x > camera_->visible_area_.x ||
           y > camera_->visible_area_.y || y < -camera_->visible_area_.y;
  };

  if (out_of_screen(projection_point.x, projection_point.y)) {
    return std::nullopt;
  }

  projection_point.x = projection_point.x / camera_->visible_area_.x;
  projection_point.y = projection_point.y / camera_->visible_area_.y;

  auto window_size = window_->window_.getSize();

  glm::vec2 screen_pos{int(((projection_point.x + 1) * window_size.x) / 2),
                       int(((1 - projection_point.y) * window_size.y) / 2)};

  return screen_pos;
}
}  // namespace silver