#pragma once

#include <vector>

class Node {
public:
  // BUILDERS
  Node() : id_(), father_(NULL), cost_() {}
  Node(int id, Node* fth, float cst) : 
    id_(id), father_(fth), cost_(cst) {}

  // GETTERS
  int ID() const { return id_; }
  Node* GetFather() { return father_; } 
  float Cost() const { return cost_; }

  // SETTERS
  void SetID(int id) { id_ = id; }
  void SetFthr(Node* fthr) { father_ = fthr; } 
  void SetCost(float cst) { cost_ = cst; }
  
private:
  int id_;
  Node* father_;
  float cost_;
};
