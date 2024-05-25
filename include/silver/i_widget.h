// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#pragma once

namespace silver {

class IWidget {
 public:
  virtual void Render() = 0;
};

}  // namespace silver