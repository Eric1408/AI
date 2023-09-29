#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

#include "node.h"

class Grafo {
public:
  //Constructores
  Grafo(std::istream&);

  //Setters
  void setNode(Node*);
  void setEdge(Node*, Node*, float);

  Node* find(int) const;

  //Recorrido
  void Anchura(int, int);

private:
  int vertices_;
  std::vector<Node*> nodos_;
  std::vector<Arista> edges_;
};
