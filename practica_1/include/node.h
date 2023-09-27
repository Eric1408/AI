#pragma once

#include <vector>

class Node {
public:
  Node();
private:
  int id_;
  Node* padre_;
  std::vector<std::pair<Node*, float>> hijos_; 
};