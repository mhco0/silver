// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)

#include <memory>
#include <string_view>

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace silver {
class Window {
 public:
  Window(int width, int height, const std::string_view& title);
  ~Window();
  Window(const Window&) = delete;
  Window(Window&& rval) = delete;
  Window& operator=(const Window&) = delete;

  void MainLoop();

 private:
  GLFWwindow* window_;
};
}  // namespace silver