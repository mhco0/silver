// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/04/2024.
// Copyright (c)

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <vector>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "silver/canvas.h"
#include "silver/projection_3d.h"
#include "silver/triangle.h"
#include "silver/window.h"

namespace silver {

namespace internal {
glm::vec2 Baricenter(const std::array<glm::vec2, 3> triangle_vertices) {
  return glm::vec2{(triangle_vertices[0].x + triangle_vertices[1].x +
                    triangle_vertices[2].x) /
                       3.0,
                   (triangle_vertices[0].y + triangle_vertices[1].y +
                    triangle_vertices[2].y) /
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

void Canvas::DrawPoint(const glm::vec2& point) {
  auto vertex_point = sf::Vertex(
      sf::Vector2f{std::round(point.x), std::round(point.y)}, sf::Color::Green);
  target_->window_.draw(&vertex_point, 1, sf::Points);
}

void Canvas::DrawPoints(const std::vector<glm::vec2>& points) {
  sf::VertexArray vertexs(sf::Lines, points.size());
  for (int i = 0; i < points.size(); ++i) {
    vertexs[i].position = sf::Vector2f{points[i].x, points[i].y};
    vertexs[i].color = sf::Color::Blue;
  }
  target_->window_.draw(vertexs);
}

void Canvas::FillTriangle(Triangle& triangle) {

  std::vector<glm::vec2> points =
      internal::ScanLine(projection_->Project(triangle.vertices[0]).value(),
                         projection_->Project(triangle.vertices[1]).value(),
                         projection_->Project(triangle.vertices[2]).value());

  DrawPoints(points);
}

void Canvas::Draw() {
  for (auto& object : objects_) {
    for (auto& triangule : object) {
      auto p0 = projection_->Project(triangule.vertices[0]);
      auto p1 = projection_->Project(triangule.vertices[1]);
      auto p2 = projection_->Project(triangule.vertices[2]);
      if (p0.has_value() && p1.has_value() && p2.has_value()) {
        // DrawPoints({
        //     p0.value(),
        //     p1.value(),
        //     p1.value(),
        //     p2.value(),
        //     p2.value(),
        //     p0.value(),
        // });
        FillTriangle(triangule);
      }

      //DrawPoint(projection_->Project(triangule.vertices[0]));
      //DrawPoint(projection_->Project(triangule.vertices[1]));
      //DrawPoint(projection_->Project(triangule.vertices[2]));
    }
  }
}

void Canvas::Clear() {
  objects_.clear();
}

void Canvas::OnUpdate(float delta_time) {
  Draw();
}

}  // namespace silver