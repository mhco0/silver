// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/16/2024.
// Copyright (c)

#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <glm/vec3.hpp>

#include <silver/application.h>
#include <silver/camera_3d.h>
#include <silver/camera_controller_widget.h>
#include <silver/canvas.h>
#include <silver/geometry_selection_widget.h>
#include <silver/utils.h>
#include <silver/window.h>

int main(void) {
  silver::Window window(800, 600, "Silver Surface Viewer");
  silver::Canvas canvas(&window);
  silver::Camera3d camera;
  silver::CameraControllerWidget camera_widget(&camera);
  silver::GeometrySelectionWidget geometry_selection_widget;
  silver::Projection3d projection(80, 60, 75, 12.0, 1);

  window.AddWidget(&camera_widget);
  window.AddWidget(&geometry_selection_widget);

  auto draw_geometry =
      [&canvas, &projection](const std::vector<std::string>& paths) -> void {
    auto geometry = silver::LoadGeometry(paths.at(0));
    for (const auto& point : geometry.value()) {
      canvas.DrawPoint(projection.Project(point));
    }
  };

  geometry_selection_widget.AddCallback(draw_geometry);

  silver::Application::SetMainWindow(&window);

  silver::Application::Run();

  return 0;
}