// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/16/2024.
// Copyright (c)

#include <format>
#include <iostream>

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "[glad] GL with GLFW", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }
  std::cout << std::format("GL {}.{}\n", GLVersion.major, GLVersion.minor)
            << std::endl;

  int channels = 0;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    channels = (channels + 1) % 8;
    glm::vec3 color((1 & channels), (1 & (channels >> 1)), (1 & (channels >> 2)));
    std::cout << std::format("{} {} {}", color.r, color.g, color.b)
              << std::endl;
    glClearColor(color.r, color.g, color.b, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}