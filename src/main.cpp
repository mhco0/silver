// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/16/2024.
// Copyright (c)

#include <format>
#include <iostream>

#include <silver/application.h>
#include <silver/window.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void) {
  std::cout << "oi" << std::endl;
  silver::Window window(800, 600, "[glad] GL with GLFW");

  silver::Application::SetMainWindow(&window);

  silver::Application::Run();

  return 0;
}