#pragma once

#include <iostream>
#include <vector>

enum ID {
  WALL,
  PATH,
  START,
  END,
  SOLUTION
};

class Node {
public:
  // BUILDERS
  Node() : coordinates_(), father_(nullptr), g_(), h_() {}
  Node(std::pair<int, int> coords) : coordinates_(coords) {}
  Node(std::pair<int, int> coord, ID id, int g = 0) : coordinates_(coord), id_(id), g_(g) {}
  
  // GETTERS
  std::pair<int, int> Coords() const { return coordinates_; }
  Node* GetFather() const { return father_; } 
  ID GetID() const { return id_; }
  int GetCost() const { return g_; }
  int GetHeur() const { return h_; }
  int GetFun() const { return f_(); }
  
  inline bool operator==(const Node& node) const {
    return this->coordinates_ == node.coordinates_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "(" << node.Coords().first << ", " << node.Coords().second << ")\n"
       << "   g = " << node.GetCost() << std::endl
       << "   h = " << node.GetHeur() << std::endl;
    if (node.GetFather() != nullptr) {
      os << "   my father is (" << node.GetFather()->Coords().first << ", " << node.GetFather()->Coords().second << ")";
    } else {
      os << "   no father";
    }
    
    return os; 
  }

  // SETTERS
  void SetID(ID id) { id_ = id; }
  void SetFthr(Node* fthr) { father_ = fthr; }
  void SetHeur(int h) { h_ = h; }
  void SetCost(int g) { g_ = g; } 
  void Reset() {
    father_ = nullptr;
    g_ = 0;
    h_ = 0;
    id_ = ID::PATH;
  }
  
private:
  std::pair<int, int> coordinates_;
  Node* father_;
  ID id_;
  inline int f_() const { return g_ + h_; } 
  int h_;
  int g_;
};
