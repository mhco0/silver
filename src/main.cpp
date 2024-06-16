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
#include <silver/projection_3d.h>
#include <silver/utils.h>
#include <silver/window.h>

int main(void) {
  silver::Window window(800, 600, "Silver Surface Viewer");
  silver::Camera3d camera;
  silver::CameraControllerWidget camera_widget(&camera);
  silver::Projection3d projection(&camera, &window);
  silver::Canvas canvas(&window, &projection);
  silver::GeometrySelectionWidget geometry_selection_widget;

  window.AddWidget(&camera_widget);
  window.AddWidget(&geometry_selection_widget);
  window.AddNode(&canvas);

  auto add_geometry =
      [&canvas, &projection](const std::vector<std::string>& paths) -> void {
    for (const auto& path : paths) {
      auto geometry = silver::LoadGeometry(path);
      canvas.AddObject(geometry.value());
    }
  };

  geometry_selection_widget.AddLoadCallback(add_geometry);

  auto clear_geometrys = [&canvas]() -> void {
    canvas.Clear();
  };

  geometry_selection_widget.AddClearCallback(clear_geometrys);

  silver::Application::SetMainWindow(&window);

  silver::Application::Run();

  return 0;
}