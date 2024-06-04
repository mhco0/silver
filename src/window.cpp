// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)

#include <format>
#include <iostream>
#include <string_view>

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <glm/vec3.hpp>

#include "silver/i_widget.h"
#include "silver/window.h"

namespace silver {
Window::Window(int width, int height, const std::string_view& title)
    : window_(sf::VideoMode(width, height), title.data()) {

  if (!ImGui::SFML::Init(window_)) {
    std::cout << "Error on init SFML on window" << std::endl;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

Window::~Window() {
  ImGui::SFML::Shutdown();
}

void Window::AddWidget(IWidget* widget) {
  widgets_.push_back(widget);
}

void Window::MainLoop() {
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  ImGuiIO& io = ImGui::GetIO();
  sf::Clock delta_clock;
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window_, event);

      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }

    ImGui::SFML::Update(window_, delta_clock.restart());

    for (const auto& widget : widgets_) {
      widget->Render();
    }

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin(
          "Hello, world!");  // Create a window called "Hello, world!" and append into it.

      ImGui::Text(
          "This is some useful text.");  // Display some text (you can use a format strings too)
      ImGui::SliderFloat(
          "float", &f, 0.0f,
          1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3(
          "clear color",
          (float*)&clear_color);  // Edit 3 floats representing a color

      if (ImGui::Button(
              "Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / io.Framerate, io.Framerate);
      ImGui::End();
    }

    ImGui::Render();
    window_.clear(clear_color);
    ImGui::SFML::Render(window_);
    window_.display();
  }
}
}  // namespace silver
