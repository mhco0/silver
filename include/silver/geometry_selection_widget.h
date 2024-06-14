// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/11/2024.
// Copyright (c)

#pragma once

#include <functional>
#include <string>
#include <vector>

#include "silver/i_widget.h"

namespace silver {
class GeometrySelectionWidget : public IWidget {
 public:
  using CallbackType = std::function<void(std::vector<std::string>)>;

  explicit GeometrySelectionWidget();

  void Render() override;

  void AddCallback(const CallbackType& callback);

  void SelectGeometrys();

 private:
  std::vector<CallbackType> on_selected_callbacks_;
};
}  // namespace silver