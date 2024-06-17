// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#include <filesystem>
#include <fstream>
#include <string>

#include <gtest/gtest.h>
#include <glm/vec3.hpp>

#include <silver/utils.h>

namespace silver {

TEST(UtilsTest, TestLoadGeometry) {
  int u_points = 3;
  int v_points = 3;
  std::vector<glm::vec3> vertices = {
      glm::vec3(20, 30, 1),      glm::vec3(10, 43, 4),  glm::vec3(32, -20, 3),
      glm::vec3(-200, 300, 100), glm::vec3(-9, 20, -3), glm::vec3(20, 10, 23),
      glm::vec3(-100, 300, 200), glm::vec3(-6, 51, -4), glm::vec3(31, 24, 54)};

  ASSERT_EQ((u_points) * (v_points), vertices.size());
  namespace fs = std::filesystem;

  auto file_path =
      fs::temp_directory_path() / "UtilsTest.TestLoadGeometry.Temp";
  std::fstream file(file_path, std::ios_base::out);
  file << u_points << v_points << "\n";
  for (const auto& vertice : vertices) {
    file << vertice.x << vertice.y << vertice.z << "\n";
  }

  file.close();

  auto expct_loaded_vertices = LoadGeometry(file_path.string());

  ASSERT_TRUE(expct_loaded_vertices.has_value());

  auto loaded_vertices = expct_loaded_vertices.value();

  ASSERT_EQ(vertices.size(), loaded_vertices.size());
  for (int i = 0; i < vertices.size(); ++i) {
    ASSERT_EQ(vertices[i], loaded_vertices[i]);
  }
}

}  // namespace silver