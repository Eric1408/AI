#pragma once

#include <vector>
#include <map>

class Node {
public:
  Node() : id_(), padre_(NULL) {}
  Node(int i) : id_(i), padre_(NULL) {}

  int getID(void) const { return id_; }
  void setID(int id) { id_ = id; }

  
  Node* getPadre(void) const { return padre_; }
  void setPadre(Node* padre) { padre_ = padre; }

  void setHijo(Node*, float);
  Node* getHijo(int i) const { return hijos_[i].first; }
  int SearchHijoID(int i) const;

private:
  int id_;
  //Para el nodo incial iniciarlo con nullptr
  Node* padre_;
  std::vector<std::pair<Node*, float>> hijos_;
};

struct Arista {
  Node* origen;
  Node* destino;
  float costo;

  Arista(Node* from, Node* to, float cost) : origen(from), destino(to), costo(cost) {}
};