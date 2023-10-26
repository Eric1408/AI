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
  // CONSTRUCTORES
  Node() : coordinates_(), father_(nullptr), g_(), h_() {} // Constructor predeterminado
  Node(std::pair<int, int> coords) : coordinates_(coords) {} // Constructor con coordenadas
  Node(std::pair<int, int> coord, ID id, int g = 0) : coordinates_(coord), id_(id), g_(g) {} // Constructor con coordenadas, tipo y costo

  // MÉTODOS GET
  std::pair<int, int> Coords() const { return coordinates_; } // Obtiene las coordenadas del nodo
  Node* GetFather() const { return father_; } // Obtiene el padre del nodo
  ID GetID() const { return id_; } // Obtiene el tipo del nodo
  int GetCost() const { return g_; } // Obtiene el costo acumulado (g)
  int GetHeur() const { return h_; } // Obtiene el valor heurístico (h)
  int GetFun() const { return f_(); } // Calcula y obtiene el valor de la función f (f = g + h)

  // SOBRECARGA DEL OPERADOR DE IGUALDAD
  inline bool operator==(const Node& node) const {
    return this->coordinates_ == node.coordinates_;
  }

  // SOBRECARGA DEL OPERADOR DE SALIDA
  friend std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "(" << node.Coords().first << ", " << node.Coords().second << ")";
    //   << "   g = " << node.GetCost() << std::endl
    //   << "   h = " << node.GetHeur() << std::endl;
    //if (node.GetFather() != nullptr) {
    //  os << "   my father is (" << node.GetFather()->Coords().first << ", " << node.GetFather()->Coords().second << ")";
    //} else {
    //  os << "   no father";
    //}
    return os; 
  }

  // MÉTODOS SET
  void SetID(ID id) { id_ = id; } // Establece el tipo del nodo
  void SetFthr(Node* fthr) { father_ = fthr; } // Establece el padre del nodo
  void SetHeur(int h) { h_ = h; } // Establece el valor heurístico (h)
  void SetCost(int g) { g_ = g; } // Establece el costo acumulado (g)
  void Reset() {
    // Restablece los atributos del nodo
    father_ = nullptr;
    g_ = 0;
    h_ = 0;
    id_ = ID::PATH;
  }
  
private:
  std::pair<int, int> coordinates_; // Coordenadas del nodo
  Node* father_; // Nodo padre
  ID id_; // Tipo del nodo
  inline int f_() const { return g_ + h_; } // Calcula y devuelve la función f (f = g + h)
  int h_; // Valor heurístico
  int g_; // Costo acumulado
};
