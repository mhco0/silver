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
  sf::VertexArray vertexs(sf::Points, points.size());
  for (int i = 0; i < points.size(); ++i) {
    vertexs[i].position = sf::Vector2f{points[i].x, points[i].y};
    vertexs[i].color = sf::Color::Blue;
  }
  target_->window_.draw(vertexs);
}

void Canvas::FillTriangle(Triangle& triangle) {
  std::array<glm::vec2, 3> projected_triangle = {
      projection_->Project(triangle.vertices.at(0)),
      projection_->Project(triangle.vertices.at(1)),
      projection_->Project(triangle.vertices.at(2)),
  };

  auto visible = [this](const glm::vec2& projected_triangle) -> bool {
    return projected_triangle.x >= 0 &&
           projected_triangle.x < target_->window_.getSize().x &&
           projected_triangle.y >= 0 &&
           projected_triangle.y < target_->window_.getSize().y;
  };

  if (!std::all_of(projected_triangle.begin(), projected_triangle.end(),
                   visible)) {
    return;
  }

  std::vector<std::pair<float, float>> tryout(projected_triangle.size());
  for (int i = 0; i < projected_triangle.size(); ++i) {
    tryout[i] = {projected_triangle[i].y, projected_triangle[i].x};
  }
  std::sort(tryout.begin(), tryout.end());

  for (int i = 0; i < projected_triangle.size(); ++i) {
    projected_triangle[i] = glm::vec2{tryout[i].second, tryout[i].first};
  }

  for (int i = 0; i < projected_triangle.size(); ++i) {
    std::cout << std::format("{}: {:1f} {:1f} \n", i,
                             std::round(projected_triangle[i].x),
                             std::round(projected_triangle[i].y));
  }

  // auto get_slope = [](const glm::vec2& p2, const glm::vec2& p1) -> float {
  //   return (p2.y - p1.y) / (p2.x - p1.x);
  // };

  std::vector<glm::vec2> points;
  // auto scan = [&get_slope, &points, &projected_triangle](
  //                 int start_y, int end_y, float xmin, float xmax, int lp1,
  //                 int lp2, int rp1, int rp2) {
  //   for (int j = start_y; j <= end_y; ++j) {
  //     int intxmin = static_cast<int>(std::round(xmin));
  //     int intxmax = static_cast<int>(std::round(xmax));
  //     for (int i = std::min(intxmin, intxmax); i <= std::max(intxmin, intxmax);
  //          ++i) {
  //       //std::cout << std::format("{} {} \n", i, j);
  //       points.emplace_back(i, j);
  //     }
  //     //if (glm::epsilonNotEqual(xmin, xmax, 1e-6f)) {
  //     xmin += std::pow(
  //         get_slope(projected_triangle[lp2], projected_triangle[lp1]), -1.0f);
  //     xmax += std::pow(
  //         get_slope(projected_triangle[rp2], projected_triangle[rp1]), -1.0f);
  //     //}
  //   }
  // };
  // float ymin = projected_triangle[0].y;
  // float xmin = projected_triangle[0].x;
  // float xmax = projected_triangle[0].x;
  // int start_y = static_cast<int>(std::round(ymin));
  // int end_y = static_cast<int>(std::round(projected_triangle[1].y));
  // int lp2 = (projected_triangle[0].x < projected_triangle[1].x) ? 1 : 0;
  // int lp1 = (projected_triangle[0].x < projected_triangle[1].x) ? 0 : 1;
  // int rp1 = (projected_triangle[0].x < projected_triangle[2].x) ? 0 : 2;
  // int rp2 = (projected_triangle[0].x < projected_triangle[2].x) ? 2 : 0;
  // scan(start_y, end_y, xmin, xmax, lp1, lp2, rp1, rp2);
  // //std::cout << std::endl;
  // ymin = projected_triangle[1].y;
  // start_y = static_cast<int>(std::round(ymin));
  // end_y = static_cast<int>(std::round(projected_triangle[2].y));
  // lp2 = (projected_triangle[1].x < projected_triangle[2].x) ? 2 : 1;
  // lp1 = (projected_triangle[1].x < projected_triangle[2].x) ? 1 : 2;
  // rp1 = (projected_triangle[0].x < projected_triangle[2].x) ? 0 : 2;
  // rp2 = (projected_triangle[0].x < projected_triangle[2].x) ? 2 : 0;
  // scan(start_y, end_y, xmin, xmax, lp1, lp2, rp1, rp2);

  float y1 = projected_triangle[0].y;
  float y2 = projected_triangle[1].y;
  float y3 = projected_triangle[2].y;

  float x1 = projected_triangle[0].x;
  float x2 = projected_triangle[1].x;
  float x3 = projected_triangle[2].x;

  // Bounding rectangle
  int minx = (int)std::min(std::min(x1, x2), x3);
  int maxx = (int)std::max(std::max(x1, x2), x3);
  int miny = (int)std::min(std::min(y1, y2), y3);
  int maxy = (int)std::max(std::max(y1, y2), y3);

  // Scan through bounding rectangle
  for (int y = miny; y < maxy; y++) {
    for (int x = minx; x < maxx; x++) {
      // When all half-space functions positive, pixel is in triangle
      if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0 &&
          (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0 &&
          (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0) {
        points.emplace_back(x, y);
      }
    }
  }

  DrawPoints(points);
  // sf::VertexArray vertexs(sf::Triangles, 3);
  // for (int i = 0; i < 3; ++i) {
  //   vertexs[i].position = sf::Vector2f{std::round(projected_triangle[i].x),
  //                                      std::round(projected_triangle[i].y)};
  //   vertexs[i].color = sf::Color::White;
  // }
  // target_->window_.draw(vertexs);
}

void Canvas::Draw() {
  for (auto& object : objects_) {
    for (auto& triangule : object) {
      FillTriangle(triangule);
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