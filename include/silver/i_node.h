// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 06/14/2024.
// Copyright (c)

#pragma once

namespace silver {

class INode {
 public:
  virtual void OnUpdate(float delta_time) {}
};

}  // namespace silver