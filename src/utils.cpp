// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <glm/gtc/epsilon.hpp>
#include <glm/vec3.hpp>
#include <tl/expected.hpp>

#include "silver/triangle.h"
#include "silver/utils.h"

namespace silver {
tl::expected<std::vector<Triangle>, std::string_view> LoadGeometry(
    const std::string& path_file) {
  std::fstream file(path_file, std::ios_base::in);
  if (!file.is_open()) {
    return tl::unexpected(std::format("Couldn't open file {}", path_file));
  }

  int u_coords{};
  int v_coords{};

  file >> u_coords >> v_coords;
  int total_points = u_coords * v_coords;
  std::vector<std::vector<glm::vec3>> vertices(
      u_coords, std::vector<glm::vec3>(v_coords));
  int num_points = 0;
  int u = 0;
  int v = 0;
  while (num_points++ < total_points) {
    glm::vec3 point{};
    file >> point.x >> point.y >> point.z;
    vertices[u][v] = point;
    v = (v + 1) % v_coords;
    if (v == 0) {
      ++u;
    }
  }

  // for (int i = 0; i < vertices.size(); ++i) {
  //   for (int j = 0; j < vertices[i].size(); ++j) {
  //     std::cout << std::format("{}, {}: {} {} {} \n", i, j, vertices[i][j].x,
  //                              vertices[i][j].y, vertices[i][j].z);
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  std::vector<Triangle> triangles;
  for (int i = 0; i <= vertices.size() - 2; ++i) {
    for (int j = 0; j <= vertices[i].size() - 2; ++j) {
      triangles.push_back(Triangle(std::array<glm::vec3, 3>{
          vertices[i][j],
          vertices[i][j + 1],
          vertices[i + 1][j],
      }));
      triangles.push_back(Triangle(std::array<glm::vec3, 3>{
          vertices[i][j + 1],
          vertices[i + 1][j + 1],
          vertices[i + 1][j],
      }));
    }
  }

  // for (const auto& triangule : triangles) {
  //   for (int i = 0; i < triangule.vertices.size(); ++i) {
  //     std::cout << std::format("{}: {} {} {}\n", i, triangule.vertices[i].x,
  //                              triangule.vertices[i].y,
  //                              triangule.vertices[i].z);
  //   }
  // }

  int total_triangles = (u_coords - 1) * (v_coords - 1) * 2;
  if (total_triangles != static_cast<int>(triangles.size())) {
    return tl::unexpected(
        std::format("Triangle mesh size not match expected: {} actual: {}",
                    total_triangles, triangles.size()));
  }

  return triangles;
}

}  // namespace silver