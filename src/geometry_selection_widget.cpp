// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/11/2024.
// Copyright (c)

#include <format>
#include <string>
#include <vector>

#include <imgui.h>
#include <nfd.h>
#include <tl/expected.hpp>

#include "silver/geometry_selection_widget.h"
#include "silver/utils.h"

namespace silver {

namespace internal {
class NfdWrapper {
 public:
  explicit NfdWrapper() : path_set_{} {}

  ~NfdWrapper() {
    if (path_set_.count > 0) {
      NFD_PathSet_Free(&path_set_);
    }
  }

  std::vector<std::string> Paths() const {
    std::vector<std::string> paths;
    for (size_t i = 0; i < NFD_PathSet_GetCount(&path_set_); ++i) {
      nfdchar_t* path = NFD_PathSet_GetPath(&path_set_, i);
      paths.emplace_back(path);
    }

    return paths;
  }

  nfdpathset_t& GetSet() { return path_set_; }

 private:
  nfdpathset_t path_set_;
};

tl::expected<std::vector<std::string>, std::string> OpenDialog() {
  constexpr const char* const kFilterText = "txt;data";
  NfdWrapper wrapper{};
  auto open_result = NFD_OpenDialogMultiple(kFilterText, "", &wrapper.GetSet());
  using tlu = tl::unexpected<std::string>;
  switch (open_result) {
    case NFD_OKAY: {
      return wrapper.Paths();
    } break;
    case NFD_CANCEL: {
      return std::vector<std::string>{};
    } break;
    default: {
      return tlu{NFD_GetError()};
    } break;
  }

  return tlu{std::format("unreacheble code under {}", __func__)};
}

}  // namespace internal

GeometrySelectionWidget::GeometrySelectionWidget() : on_selected_callbacks_{} {}

void GeometrySelectionWidget::AddLoadCallback(
    const LoadCallbackType& callback) {
  on_selected_callbacks_.push_back(callback);
}

void GeometrySelectionWidget::AddClearCallback(
    const ClearCallbackType& callback) {
  on_clear_callbacks_.push_back(callback);
}

void GeometrySelectionWidget::SelectGeometrys() {
  auto selected_paths = internal::OpenDialog();
  if (!selected_paths.has_value()) {
    auto error = selected_paths.error();
    ImGui::LogText(error.c_str());
    return;
  }

  for (auto& callback : on_selected_callbacks_) {
    callback(selected_paths.value());
  }
}

void GeometrySelectionWidget::ClearGeometrys() {
  for (auto& callback : on_clear_callbacks_) {
    callback();
  }
}

void GeometrySelectionWidget::Render() {
  ImGui::Begin("Geometry Selection");
  if (ImGui::Button("Load Geometry")) {
    SelectGeometrys();
  }
  if (ImGui::Button("Clear Geometry")) {
    ClearGeometrys();
  }
  ImGui::End();
}

}  // namespace silver