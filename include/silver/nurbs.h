// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/30/2024.
// Copyright (c)
#pragma once

#include <vector>

#include <glm/vec3.hpp>

namespace silver {

struct NurbsConfig {
  int n_u;
  int n_v;
  int k_u;
  int k_v;
  int k_r_u;
  int k_r_v;
  int c_u;
  int c_v;
  int p_u;
  int p_v;
  std::vector<float> u_nodes;
  std::vector<int> repeated_u_node;
  std::vector<float> v_nodes;
  std::vector<int> repeated_v_node;
  std::vector<std::vector<glm::vec3>> control_points;
  std::vector<std::vector<float>> weigths_matrix;
};

struct NurbsSurface {
  int p_u;
  int p_v;
  std::vector<glm::vec3> surface_points;
};

NurbsSurface Nurbs(const NurbsConfig& nurbs_config);

}  // namespace silver