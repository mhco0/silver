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
  ImGui::SliderFloat3("Normal", glm::value_ptr(camera_->normal_), 0.0f, 1.0f);
  ImGui::End();
}

}  // namespace silver