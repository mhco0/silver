// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 05/25/2024.
// Copyright (c)

#pragma once

#include "silver/i_node.h"

namespace silver {

class IWidget : public INode {
 public:
  virtual void Render() = 0;
};

}  // namespace silver