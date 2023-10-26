#pragma once

#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>

#include "node.h"

typedef std::vector<std::vector<int>> matrix;
typedef std::vector<std::vector<Node*>> n_matrix;

class Maze {
public:
  // BUILDERS
  Maze(std::ifstream&);

  // METHODS
  void ResetM();
  void SetNewStart(int, int);
  void SetNewEnd(int, int);
  void Resolve(bool);
  bool AStar(bool);
  void PrintNM();
  std::vector<Node*> GetNeighbors(Node*);
  
private:
  Node* start_;
  Node* end_;
  int x_;
  int y_;
  n_matrix nmatrix_;
};
