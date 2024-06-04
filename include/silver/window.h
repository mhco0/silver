// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/20/2024.
// Copyright (c)
#pragma once

#include <memory>
#include <string_view>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "silver/i_widget.h"

namespace silver {
class Canvas;
class Window {
 public:
  Window(int width, int height, const std::string_view& title);
  ~Window();
  Window(const Window&) = delete;
  Window(Window&& rval) = delete;
  Window& operator=(const Window&) = delete;

  void AddWidget(IWidget* widget);
  void MainLoop();

 private:
  sf::RenderWindow window_;
  std::vector<IWidget*> widgets_;
  friend class Canvas;
};
}  // namespace silver