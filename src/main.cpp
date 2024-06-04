// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/16/2024.
// Copyright (c)

#include <format>
#include <iostream>

#include <silver/application.h>
#include <silver/camera_3d.h>
#include <silver/camera_controller_widget.h>
#include <silver/canvas.h>
#include <silver/window.h>

int main(void) {
  silver::Window window(800, 600, "Silver Surface Viewer");
  silver::Camera3d camera;
  silver::CameraControllerWidget camera_widget(&camera);
  silver::Canvas canvas(&window);

  canvas.DrawPoint(500, 300);

  window.AddWidget(&camera_widget);

  silver::Application::SetMainWindow(&window);

  silver::Application::Run();

  return 0;
}