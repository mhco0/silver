// Created by Marcos Oliveira <mhco@cin.ufpe.br> and Diego Fernando <dffa@cin.ufpe.br> on 06/30/2024.
// Copyright (c)

#include <vector>

#include <glm/vec3.hpp>

#include "silver/nurbs.h"

namespace silver {

namespace internal {

float N0_i(int i, float curve_parameter, const std::vector<float>& nodes) {
  if (i >= 0 && curve_parameter >= nodes[i - 1] && curve_parameter < nodes[i]) {
    return 1.0f;
  }

  return 0.0f;
}

float Nk_l(int k, int l, float curve_parameter,
           const std::vector<float>& nodes) {
  if (k == 1) {
    return (curve_parameter - nodes[l - 1]) /
               (nodes[l + k - 1] - nodes[l - 1]) *
               internal::N0_i(l, curve_parameter, nodes) +
           (nodes[l + k] - curve_parameter) / (nodes[l + k] - nodes[l]) *
               internal::N0_i(l + 1, curve_parameter, nodes);
  }

  return (curve_parameter - nodes[l - 1]) / (nodes[l + k - 1] - nodes[l - 1]) *
             internal::Nk_l(k - 1, l, curve_parameter, nodes) +
         (nodes[l + k] - curve_parameter) / (nodes[l + k] - nodes[l]) *
             internal::Nk_l(k - 1, l + 1, curve_parameter, nodes);
}

glm::vec3 calculate_surface_point(float u, float v,
                                  const NurbsConfig& nurbs_config) {
  glm::vec3 surface_point = {0.0f, 0.0f, 0.0f};
  float coeff_control_points = 0.0f;
  float coeff_sum = 0.0f;

  for (int row = 1; row < nurbs_config.c_v - 1; row++) {
    for (int col = 1; col < nurbs_config.c_u - 1; col++) {
      auto nk_lu =
          internal::Nk_l(nurbs_config.n_u, col, u, nurbs_config.u_nodes);
      auto nk_lv =
          internal::Nk_l(nurbs_config.n_v, row, v, nurbs_config.v_nodes);
      coeff_control_points =
          nurbs_config.weigths_matrix[row][col] * nk_lu * nk_lv;

      coeff_sum += coeff_control_points;

      surface_point +=
          nurbs_config.control_points[row][col] * coeff_control_points;
    }
  }

  surface_point /= coeff_sum;
  return surface_point;
}

}  // namespace internal

NurbsSurface Nurbs(const NurbsConfig& nurbs_config) {
  auto calculate_delta = [](int num_control_points, int spline_degree,
                            int num_points_on_surface,
                            const std::vector<float>& nodes) -> float {
    return (nodes[num_control_points - 1] - nodes[spline_degree - 1]) /
           num_points_on_surface;
  };

  float delta_u = calculate_delta(nurbs_config.c_u, nurbs_config.n_u,
                                  nurbs_config.p_u, nurbs_config.u_nodes);

  float delta_v = calculate_delta(nurbs_config.c_v, nurbs_config.n_v,
                                  nurbs_config.p_v, nurbs_config.v_nodes);

  float u = nurbs_config.u_nodes[nurbs_config.n_u - 1] - delta_u;
  float v = nurbs_config.v_nodes[nurbs_config.n_v - 1] - delta_v;

  NurbsSurface surface{};
  surface.p_u = nurbs_config.p_u;
  surface.p_v = nurbs_config.p_v;
  for (int i = 0; i < nurbs_config.p_v; i++) {
    v = v + delta_v;
    for (int j = 0; j < nurbs_config.p_u; j++) {
      u = u + delta_u;

      auto point = internal::calculate_surface_point(u, v, nurbs_config);

      surface.surface_points.push_back(point);
    }
    u = nurbs_config.u_nodes[nurbs_config.n_u - 1] - delta_u;
  }

  return surface;
}

}  // namespace silver
