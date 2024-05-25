// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/16/2024.
// Copyright (c)

#include <format>
#include <iostream>

#include <silver/application.h>
#include <silver/window.h>

int main(void) {
  silver::Window window(800, 600, "Silver Surface Viewer");

  silver::Application::SetMainWindow(&window);

  silver::Application::Run();

  return 0;
}