// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <tl/expected.hpp>

#include "silver/triangle.h"

namespace silver {
tl::expected<std::vector<Triangle>, std::string_view> LoadGeometry(
    const std::string& path_file);
};  // namespace silver