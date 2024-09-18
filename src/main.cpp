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
#include <silver/nurbs.h>
#include <silver/object_3d.h>
#include <silver/projection_3d.h>
#include <silver/utils.h>
#include <silver/window.h>

int main(void) {
  silver::Window window(700, 700, "Silver Surface Viewer");
  silver::Camera3d camera;
  silver::CameraControllerWidget camera_widget(&camera);
  silver::Projection3d projection(&camera, &window);
  silver::Canvas canvas(&window, &projection);
  silver::GeometrySelectionWidget geometry_selection_widget;

  window.AddWidget(&camera_widget);
  window.AddWidget(&geometry_selection_widget);
  window.AddNode(&canvas);

  auto add_geometry = [&camera, &canvas, &projection](
                          const std::vector<std::string>& paths) -> void {
    for (const auto& path : paths) {
      if (path.ends_with("data")) {
        auto nurbs_and_camera_config = silver::LoadNurbsAndCameraConfig(path);

        if (nurbs_and_camera_config.has_value()) {
          auto [nurbs_config, camera_config] = nurbs_and_camera_config.value();
          camera.Set(camera_config);
          auto surface = silver::Nurbs(nurbs_config);
          silver::SaveSurface(surface, "./assets/nurbs.txt");
          auto geometry = silver::LoadGeometry("./assets/nurbs.txt");
          silver::Object3d object(geometry.value());
          canvas.AddObject(object);
        }
      } else {
        auto geometry = silver::LoadGeometry(path);
        silver::Object3d object(geometry.value());
        canvas.AddObject(object);
      }
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