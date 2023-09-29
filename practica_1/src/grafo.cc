#include "../include/grafo.h"

#include <string>

Grafo::Grafo(std::istream& ifstrm) {
  std::string line;
  std::getline(ifstrm, line);
  vertices_ = stoi(line);
  
  //Gauss Sum
  for (int i = 1; i < vertices_; ++i) {
    Node* padre = new Node(i);
    nodos_.push_back(padre);
    for (int j = i+1; j <= vertices_; ++j) {
      //Obtengo la distancia
      std::getline(ifstrm, line);
      float distance = std::stof(line);
      if (distance > -1) {
        //Creo un nodo que sera nodo hijo
        Node* hijo = new Node(j);
        padre->setHijo(hijo, distance);
        hijo->setPadre(padre);
        //Arista edge(padre, hijo, distance);
        //edges_.push_back(edge);
      }
    }
  }


  for (size_t i = 0; i < edges_.size(); ++i) {
    std::cout << edges_[i].origen->getID() << " " << edges_[i].destino->getID() << " costo = " << edges_[i].costo << std::endl;
  }
}

Node* Grafo::find(int id) const {
  for (size_t i = 0; i < nodos_.size(); ++i) {
    if (nodos_[i]->getID() == id) {
      return nodos_[i];
    } else if (nodos_[i]->SearchHijoID(id)) {
      return nodos_[i]->getHijo(id);
    }
  }
}

void Grafo::Anchura(int init, int fin) {
  std::queue<Node*> cola;
  if (find(init)) cola.push(find(init));
  
  for ()
}






//Estructura matriz para alacenar el grfo y luego una estructura para crear el arbol 


