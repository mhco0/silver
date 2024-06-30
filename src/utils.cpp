// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#include <format>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include <glm/gtc/epsilon.hpp>
#include <glm/vec3.hpp>
#include <tl/expected.hpp>

#include "silver/camera_3d.h"
#include "silver/nurbs.h"
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

  int total_triangles = (u_coords - 1) * (v_coords - 1) * 2;
  if (total_triangles != static_cast<int>(triangles.size())) {
    return tl::unexpected(
        std::format("Triangle mesh size not match expected: {} actual: {}",
                    total_triangles, triangles.size()));
  }

  return triangles;
}

tl::expected<std::pair<NurbsConfig, CameraConfig>, std::string_view>
LoadNurbsAndCameraConfig(const std::string& path_file) {
  std::fstream file(path_file, std::ios_base::in);
  if (!file.is_open()) {
    return tl::unexpected(std::format("Couldn't open file {}", path_file));
  }

  NurbsConfig nurbs_config{};

  file >> nurbs_config.n_u >> nurbs_config.n_v >> nurbs_config.k_u >>
      nurbs_config.k_v >> nurbs_config.k_r_u >> nurbs_config.k_r_v;

  nurbs_config.repeated_u_node = std::vector<int>(nurbs_config.k_u);
  nurbs_config.repeated_v_node = std::vector<int>(nurbs_config.k_v);
  nurbs_config.u_nodes = std::vector<float>(nurbs_config.k_r_u);
  nurbs_config.v_nodes = std::vector<float>(nurbs_config.k_r_v);

  auto read_repeated = [&file](int knots, std::vector<float>& nodes,
                               std::vector<int>& repeated) {
    int index = 0;
    for (int line = 0; line < knots; ++line) {
      float temp{};
      file >> temp >> repeated[line];
      for (int repetion = 0; repetion < repeated[line]; ++repetion) {
        nodes[index] = temp;
        ++index;
      }
    }
  };

  read_repeated(nurbs_config.k_u, nurbs_config.u_nodes,
                nurbs_config.repeated_u_node);

  read_repeated(nurbs_config.k_v, nurbs_config.v_nodes,
                nurbs_config.repeated_v_node);

  int c_u = nurbs_config.k_r_u + 1 - nurbs_config.n_u;
  nurbs_config.c_u = c_u;
  int c_v = nurbs_config.k_r_v + 1 - nurbs_config.n_v;
  nurbs_config.c_v = c_v;
  nurbs_config.control_points =
      std::vector<std::vector<glm::vec3>>(c_v, std::vector<glm::vec3>(c_u));

  nurbs_config.weigths_matrix =
      std::vector<std::vector<float>>(c_v, std::vector<float>(c_u));

  for (int i = 0; i < c_v; i++) {
    for (int j = 0; j < c_u; j++) {
      file >> nurbs_config.control_points[i][j].x >>
          nurbs_config.control_points[i][j].y >>
          nurbs_config.control_points[i][j].z >>
          nurbs_config.weigths_matrix[i][j];
    }
  }

  CameraConfig camera_config{};

  file >> camera_config.focus.x >> camera_config.focus.y >>
      camera_config.focus.z;
  file >> camera_config.n.x >> camera_config.n.y >> camera_config.n.z;
  file >> camera_config.v.x >> camera_config.v.y >> camera_config.v.z;
  file >> camera_config.distance_from_projection;

  file >> camera_config.visible_area.x >> camera_config.visible_area.y;

  file >> nurbs_config.p_u >> nurbs_config.p_v;

  return tl::expected<std::pair<NurbsConfig, CameraConfig>, std::string_view>(
      std::make_pair(nurbs_config, camera_config));
}

bool SaveSurface(const NurbsSurface& surface, const std::string& path_file) {
  std::fstream file(path_file, std::ios_base::out);
  if (!file.is_open()) {
    return false;
  }

  file << std::format("{} {}\n", surface.p_u, surface.p_v);
  for (const auto& point : surface.surface_points) {
    file << std::format("{} {} {}\n", point.x, point.y, point.z);
  }

  return true;
}

}  // namespace silver