// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#include <string>
#include <string_view>
#include <vector>

#include <glm/vec3.hpp>
#include <tl/expected.hpp>

namespace silver {
tl::expected<std::vector<glm::vec3>, std::string_view> LoadGeometry(
    const std::string& path_file);
};