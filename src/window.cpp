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
    ImGui::LogText("Error on init SFML on window");
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

Window::~Window() {
  ImGui::SFML::Shutdown(window_);
}

void Window::AddWidget(IWidget* widget) {
  nodes_.push_back(widget);
}

void Window::AddNode(INode* node) {
  nodes_.push_back(node);
}

void Window::MainLoop() {
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  ImGuiIO& io = ImGui::GetIO();
  sf::Clock delta_clock;

  window_.setFramerateLimit(60);

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window_, event);

      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }
    window_.clear(clear_color);

    ImGui::SFML::Update(window_, delta_clock.restart());
    for (const auto& node : nodes_) {
      IWidget* node_as_widget = dynamic_cast<IWidget*>(node);
      if (node_as_widget != nullptr) {
        node_as_widget->Render();
      }
      node->OnUpdate(delta_clock.getElapsedTime().asSeconds());
    }

    ImGui::SFML::Render(window_);
    window_.display();
  }
}
}  // namespace silver
