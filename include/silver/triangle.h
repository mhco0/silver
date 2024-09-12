// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/16/2024.
// Copyright (c)

#pragma once

#include <array>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace silver {

struct Triangle {
  std::array<glm::vec3, 3> vertices;
};

}  // namespace silver