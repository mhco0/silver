// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "silver/camera_controller_widget.h"

namespace silver {
CameraControllerWidget::CameraControllerWidget(Camera3d* camera)
    : camera_(camera) {}

void CameraControllerWidget::Render() {
  ImGui::Begin("Camera Controller");
  ImGui::SliderFloat3("Normal", glm::value_ptr(camera_->normal_), 0.0f, 1.0f,
                      "%.2f");
  ImGui::SliderFloat3("Focus", glm::value_ptr(camera_->focus_), 0.0f, 1.0f,
                      "%.2f");
  ImGui::SliderFloat3("Forward", glm::value_ptr(camera_->forward_), 0.0f, 1.0f,
                      "%.2f");
  ImGui::SliderFloat("Distance from projection",
                     &camera_->distance_from_projection_, 0.0, 100.0f);
  ImGui::Spacing();
  ImGui::End();
}

}  // namespace silver