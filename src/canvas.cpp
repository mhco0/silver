// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/04/2024.
// Copyright (c)

#include <algorithm>
#include <array>
#include <vector>

#include <SFML/Graphics/Vertex.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "silver/canvas.h"
#include "silver/projection_3d.h"
#include "silver/window.h"

namespace silver {
Canvas::Canvas(Window* target, Projection3d* projection)
    : target_(target), projection_(projection), objects_{} {}

void Canvas::AddObject(const std::vector<glm::vec3>& object) {
  objects_.push_back(object);
}

void Canvas::DrawPoint(const glm::vec2& point) {
  auto vertex_point = sf::Vertex(
      sf::Vector2f{std::round(point.x), std::round(point.y)}, sf::Color::White);
  target_->window_.draw(&vertex_point, 1, sf::Points);
}

void Canvas::FillTriangle(std::array<glm::vec2, 3>& triangle) {
  auto sort_by_y_x = [](const glm::vec2& lhs, const glm::vec2& rhs) {
    if (lhs.y > rhs.y) {
      return true;
    } else if (glm::epsilonEqual(lhs.y, rhs.y, 1e-6f)) {
      return lhs.x >= rhs.x;
    }
    return false;
  };
  //std::sort(triangle.begin(), triangle.end(), sort_by_y_x);

  auto get_slope = [](const glm::vec2& p1, const glm::vec2& p2) {
    return (p2.y - p1.y) / (p2.x - p1.x);
  };

  std::array<float, 3> slopes = {
      get_slope(triangle[0], triangle[1]),
      get_slope(triangle[0], triangle[2]),
      get_slope(triangle[1], triangle[2]),
  };

  int y0 = std::round(triangle[0].y);
  int y1 = std::round(triangle[1].y);
  int y2 = std::round(triangle[2].y);
  float x_min = triangle[0].x;
  float x_max = triangle[0].x;
  for (int i = y0; i <= y2; ++i) {
    if (i <= y1) {
      x_min += 1.0 / slopes[0];
    } else {
      x_min += 1.0 / slopes[2];
    }
    x_max += 1.0 / slopes[1];
    for (int j = std::round(x_min); j <= static_cast<int>(std::round(x_max));
         ++j) {
      DrawPoint(glm::vec2{j, i});
    }
  }
}

void Canvas::Draw() {
  for (auto& object : objects_) {
    auto sort_by_y = [](const glm::vec3& lhs, const glm::vec3& rhs) -> bool {
      if (lhs.y > rhs.y) {
        return true;
      } else if (glm::epsilonEqual(lhs.y, rhs.y, 1e-6f)) {
        if (lhs.x > rhs.x) {
          return true;
        } else if (glm::epsilonEqual(lhs.x, rhs.x, 1e-6f)) {
          return lhs.z > rhs.z;
        }
      }
      return false;
    };
    std::sort(object.begin(), object.end(), sort_by_y);
    for (int i = 0, j = 1, z = 2; z < object.size(); i += 3, j += 3, z += 3) {
      std::array<glm::vec2, 3> triangle = {projection_->Project(object[i]),
                                           projection_->Project(object[j]),
                                           projection_->Project(object[z])};
      auto visible = [this](const glm::vec2& triangle) -> bool {
        return triangle.x >= 0 && triangle.x < target_->window_.getSize().x &&
               triangle.y >= 0 && triangle.y < target_->window_.getSize().y;
      };
      if (std::all_of(triangle.begin(), triangle.end(), visible)) {
        FillTriangle(triangle);
      }
    }
    // for (const auto& point : object) {
    //   DrawPoint(projection_->Project(point));
    // }
  }
}

void Canvas::Clear() {
  objects_.clear();
}

void Canvas::OnUpdate(float delta_time) {
  Draw();
}

}  // namespace silver