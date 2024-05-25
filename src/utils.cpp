// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#include <format>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include <glm/vec3.hpp>
#include <tl/expected.hpp>

#include "silver/utils.h"

namespace silver {
tl::expected<std::vector<glm::vec3>, std::string_view> LoadGeometry(
    const std::string& path_file) {
  std::fstream file(path_file, std::ios_base::in);
  if (!file.is_open()) {
    return tl::unexpected(std::format("Couldn't open file {}", path_file));
  }

  int u_coords{};
  int v_coords{};

  file >> u_coords >> v_coords;
  --v_coords;
  --u_coords;
  int total_points = (u_coords * v_coords) << 1;
  std::vector<glm::vec3> vertices;
  int point = 0;
  while (++point < total_points) {
    glm::vec3 point;
    file >> point.x >> point.y >> point.z;
    vertices.emplace_back(point);
  }

  return vertices;
}

}  // namespace silver