// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/24/2024.
// Copyright (c)
#pragma once

#include <iostream>
#include <memory>

#include "silver/window.h"

namespace silver {
class Application {
 public:
  Application(Application& other) = delete;
  void operator=(const Application&) = delete;

  static void SetMainWindow(Window* target) {
    GetInstance().main_window_ = target;
  }

  static void Run() {
    if (GetInstance().main_window_ == nullptr) {
      return;
    }

    GetInstance().main_window_->MainLoop();
  }

 protected:
  Application() {}

  static Application& GetInstance() {
    static Application instance;

    return instance;
  }

  Window* main_window_{};
};

}  // namespace silver