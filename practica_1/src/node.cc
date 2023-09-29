#include "../include/node.h"

void Node::setHijo(Node* hijo, float coste) {
  hijos_.emplace_back(hijo, coste);
}

int Node::SearchHijoID(int i) const {
  for (auto hijo : hijos_) {
    if (hijo.first->getID() == i) {
      return i;
    }
  }
}
