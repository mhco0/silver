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
  using LoadCallbackType = std::function<void(std::vector<std::string>)>;
  using ClearCallbackType = std::function<void(void)>;

  explicit GeometrySelectionWidget();

  void Render() override;

  void AddLoadCallback(const LoadCallbackType& callback);
  void AddClearCallback(const ClearCallbackType& callback);

  void SelectGeometrys();
  void ClearGeometrys();

 private:
  std::vector<LoadCallbackType> on_selected_callbacks_;
  std::vector<ClearCallbackType> on_clear_callbacks_;
};
}  // namespace silver