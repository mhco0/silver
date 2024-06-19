// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/04/2024.
// Copyright (c)

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "silver/canvas.h"
#include "silver/projection_3d.h"
#include "silver/triangle.h"
#include "silver/window.h"

namespace silver {

namespace internal {
glm::vec3 BaricenterCoordinates(
    const std::array<glm::vec2, 3>& triangule_vertices,
    const glm::vec2& point) {
  glm::vec2 v0 = triangule_vertices[1] - triangule_vertices[0];
  glm::vec2 v1 = triangule_vertices[2] - triangule_vertices[0];
  glm::vec2 v2 = point - triangule_vertices[0];

  float d00 = glm::dot(v0, v0);
  float d01 = glm::dot(v0, v1);
  float d11 = glm::dot(v1, v1);
  float d20 = glm::dot(v2, v0);
  float d21 = glm::dot(v2, v1);
  float denom = d00 * d11 - d01 * d01;
  float w = (d11 * d20 - d01 * d21) / denom;
  float v = (d00 * d21 - d01 * d20) / denom;
  float u = 1.0f - v - w;
  return glm::vec3{u, v, w};
}

glm::vec2 Baricenter(const std::array<glm::vec2, 3>& triangule_vertices) {
  return glm::vec2{(triangule_vertices[0].x + triangule_vertices[1].x +
                    triangule_vertices[2].x) /
                       3.0,
                   (triangule_vertices[0].y + triangule_vertices[1].y +
                    triangule_vertices[2].y) /
                       3.0};
}

std::vector<glm::vec2> ScanLine(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2) {
  if (p0.y > p1.y) {
    std::swap(p0, p1);
  }
  if (p1.y > p2.y) {
    std::swap(p1, p2);
  }
  if (p0.y > p1.y) {
    std::swap(p0, p1);
  }

  int x0 = p0.x;
  int y0 = p0.y;
  int x1 = p1.x;
  int y1 = p1.y;
  int x2 = p2.x;
  int y2 = p2.y;

  auto interpolate = [](int y, int y0, int x0, int y1, int x1) {
    return x0 + (x1 - x0) * (y - y0) / (y1 - y0);
  };

  std::vector<glm::vec2> points;
  for (int y = y0; y <= y1; y++) {
    int start_x = (y1 != y0) ? interpolate(y, y0, x0, y1, x1) : x1;
    int end_x = (y2 != y0) ? interpolate(y, y0, x0, y2, x2) : x2;
    if (start_x > end_x)
      std::swap(start_x, end_x);
    for (int x = start_x; x <= end_x; x++) {
      points.emplace_back(x, y);
    }
  }

  for (int y = y1; y <= y2; y++) {
    int start_x = (y1 != y2) ? interpolate(y, y1, x1, y2, x2) : x2;
    int end_x = (y2 != y0) ? interpolate(y, y0, x0, y2, x2) : x2;
    if (start_x > end_x)
      std::swap(start_x, end_x);
    for (int x = start_x; x <= end_x; x++) {
      points.emplace_back(x, y);
    }
  }
  return points;
}
}  // namespace internal

Canvas::Canvas(Window* target, Projection3d* projection)
    : target_(target), projection_(projection), objects_{} {}

void Canvas::AddObject(const std::vector<Triangle>& object) {
  objects_.push_back(object);
}

void Canvas::DrawPoint(const glm::vec2& point, const sf::Color& color) {
  auto vertex_point =
      sf::Vertex(sf::Vector2f{std::round(point.x), std::round(point.y)}, color);
  target_->window_.draw(&vertex_point, 1, sf::Points);
}

void Canvas::DrawPoints(const std::vector<glm::vec2>& points,
                        const sf::Color& color) {
  sf::VertexArray vertexs(sf::Points, points.size());
  for (int i = 0; i < points.size(); ++i) {
    vertexs[i].position =
        sf::Vector2f{std::round(points[i].x), std::round(points[i].y)};
    vertexs[i].color = color;
  }
  target_->window_.draw(vertexs);
}

void Canvas::DrawPoints(const std::vector<glm::vec2>& points,
                        const std::vector<sf::Color>& colors) {
  sf::VertexArray vertexs(sf::Points, points.size());
  for (int i = 0; i < points.size(); ++i) {
    vertexs[i].position =
        sf::Vector2f{std::round(points[i].x), std::round(points[i].y)};
    vertexs[i].color = colors[i];
  }
  target_->window_.draw(vertexs);
}

void Canvas::FillTriangle(Triangle& triangle) {
  std::array<glm::vec2, 3> projections = {
      projection_->Project(triangle.vertices[0]).value(),
      projection_->Project(triangle.vertices[1]).value(),
      projection_->Project(triangle.vertices[2]).value()};

  std::vector<glm::vec2> points =
      internal::ScanLine(projections[0], projections[1], projections[2]);

  constexpr int kNumWhiteTones = 5;
  constexpr int kWhiteTonesDelta = 255 / kNumWhiteTones;

  std::vector<sf::Color> white_tones(kNumWhiteTones);
  for (int i = 0, j = 0; i <= 255 && j < kNumWhiteTones;
       i += kWhiteTonesDelta, ++j) {
    white_tones[j] = sf::Color(i, i, i, 255);
  }

  auto baricenter = internal::Baricenter(projections);

  auto tone_index =
      static_cast<int>(((target_->window_.getSize().y - baricenter.y) /
                        target_->window_.getSize().y) *
                       kNumWhiteTones);

  DrawPoints(points, white_tones[tone_index]);
}

void Canvas::Draw() {
  auto to_index_buffer = [](const glm::vec2& position, int columns) -> size_t {
    size_t x_idx = static_cast<size_t>(std::round(position.x));
    size_t y_idx = static_cast<size_t>(std::round(position.y));
    return x_idx * columns + y_idx;
  };

  std::unordered_map<size_t, float> z_buffer;
  std::unordered_map<size_t, sf::Color> colors;

  auto color_by_point = [](const float& normalized_height) -> sf::Color {
    glm::uint8 gray_scale = static_cast<glm::uint8>(normalized_height * 255.0f);
    return sf::Color{gray_scale, gray_scale, gray_scale, 255};
  };

  std::vector<glm::vec2> render_points;
  std::vector<sf::Color> render_colors;
  auto size = target_->window_.getSize();
  for (auto& object : objects_) {
    for (auto& triangule : object) {
      auto p0 = projection_->Project(triangule.vertices[0]);
      auto p1 = projection_->Project(triangule.vertices[1]);
      auto p2 = projection_->Project(triangule.vertices[2]);
      if (p0.has_value() && p1.has_value() && p2.has_value()) {
        std::vector<glm::vec2> points =
            internal::ScanLine(p0.value(), p1.value(), p2.value());
        for (const auto& point : points) {
          glm::vec3 coeff = internal::BaricenterCoordinates(
              {p0.value(), p1.value(), p2.value()}, point);
          glm::vec3 view_point =
              projection_->camera_->Translate(triangule.vertices[0]) * coeff.x +
              projection_->camera_->Translate(triangule.vertices[1]) * coeff.y +
              projection_->camera_->Translate(triangule.vertices[2]) * coeff.z;
          size_t matriz_index = to_index_buffer(point, size.y);

          if (!z_buffer.contains(matriz_index) ||
              view_point.z < z_buffer[matriz_index]) {
            auto baricenter =
                internal::Baricenter({p0.value(), p1.value(), p2.value()});

            colors[matriz_index] =
                color_by_point((size.y - baricenter.y) / size.y);
            z_buffer[matriz_index] = view_point.z;
          }

          render_points.push_back(point);
        }
      }
    }
  }

  for (const auto& point : render_points) {
    size_t matriz_index = to_index_buffer(point, size.y);
    render_colors.push_back(colors[matriz_index]);
  }

  DrawPoints(render_points, render_colors);
}

void Canvas::Clear() {
  objects_.clear();
}

void Canvas::OnUpdate(float delta_time) {
  Draw();
}

}  // namespace silver