// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/16/2024.
// Copyright (c)

#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <silver/application.h>
#include <silver/camera_3d.h>
#include <silver/camera_controller_widget.h>
#include <silver/canvas.h>
#include <silver/geometry_selection_widget.h>
#include <silver/window.h>

int main(void) {
  silver::Window window(800, 600, "Silver Surface Viewer");
  silver::Camera3d camera;
  silver::CameraControllerWidget camera_widget(&camera);
  silver::GeometrySelectionWidget geometry_selection_widget;

  window.AddWidget(&camera_widget);
  window.AddWidget(&geometry_selection_widget);

  auto print_string = [](const std::string& str) -> void {
    std::cout << std::format("{}\n", str);
  };

  auto print_strings =
      [&print_string](const std::vector<std::string>& strs) -> void {
    std::for_each(strs.begin(), strs.end(), print_string);
  };

  geometry_selection_widget.AddCallback(print_strings);

  silver::Application::SetMainWindow(&window);

  silver::Application::Run();

  return 0;
}