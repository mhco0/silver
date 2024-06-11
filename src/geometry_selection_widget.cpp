// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/11/2024.
// Copyright (c)

#include <string>
#include <vector>

#include <imgui.h>
#include <nfd.h>

#include "silver/geometry_selection_widget.h"
#include "silver/utils.h"

namespace silver {
GeometrySelectionWidget::GeometrySelectionWidget() : on_selected_callbacks_{} {}

void GeometrySelectionWidget::AddCallback(const CallbackType& callback) {
  on_selected_callbacks_.push(callback);
}

void GeometrySelectionWidget::Render() {
  ImGui::Begin("Geometry Selection");
  if (ImGui::Button("Load Geometry")) {
    nfdpathset_t outPath;
    nfdresult_t result = NFD_OpenDialogMultiple("txt", nullptr, &outPath);
    if (result == NFD_OKAY) {
      puts("Success!");

      for (int i = 0; i < outPath.count; ++i) {
        puts(outPath.buf);
      }
      free(outPath.buf);

    } else if (result == NFD_CANCEL) {
      puts("User pressed cancel.");
    } else {
      printf("Error: %s\n", NFD_GetError());
    }
  }
  ImGui::End();
}
}  // namespace silver