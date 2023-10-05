#pragma once

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <random>
#include <queue>

#include "node.h"

typedef std::unordered_map<int, std::unordered_map<int, float>> path; 


struct Grafo {
  int vertices;
  path nodes;
  Grafo(int v) : vertices(v) {}

  void AddEdge(int origin, int dest, float cost) { 
    nodes[origin][dest] = cost; 
    nodes[dest][origin] = cost;
  }
};

void PrintGraph(const Grafo& gr) {
  for (const auto& par : gr.nodes) {
    std::cout << par.first << ":\n";
    for (const auto& neighbor : par.second) {
      int dest = neighbor.first;
      float cost = neighbor.second;
      std::cout << "  " << dest << " = " << cost << std::endl;
    }
  }
}

// Modificacion: Modificar la busqueda en amplitud para que, en cada iteracion, inspeccione
// uno de los dos mejores nodos de la frontera(el de menor coste), seleccionado al azar.
// La busqueda finalizara cuando el nodo a inspeccionoar coincida con el nodo destino.

void BFS(Grafo& grafo, int init, int end, std::ofstream& out) {
  std::queue<Node*> cola;
  std::unordered_set<int> visited;
  std::unordered_set<int> generados;
  std::unordered_set<int> inspect;

  cola.push(new Node(init));
  visited.insert(init);
  
  while (!cola.empty()) {
    Node* current = cola.front();
    cola.pop();
    inspect.insert(current->ID());

    if (current->ID() == end) {
      out << "Camino: ";
      Node* nodo = current;
      while (nodo != nullptr) {
        out << nodo->ID() << " ";
        nodo = nodo->GetFather();
      }
      out << "\nNodos visitados: ";
      for (auto &i : inspect) {
        out << i << " ";
      }

      out << "\nNodos generados: ";
      for (auto &i : generados) {
        out << i << " ";
      }

      out << std::endl;
      out << "Costo total: " << current->Cost() << std::endl;

      return;
    }

    for (const auto& neighbor: grafo.nodes[current->ID()]) {
      int nodeNeighbor = neighbor.first; 
      int costEdge = neighbor.second;
      generados.insert(nodeNeighbor);

      if (visited.find(nodeNeighbor) == visited.end()) {
        visited.insert(nodeNeighbor);
        cola.push(new Node(nodeNeighbor, current, current->Cost() + costEdge));
      }
    }
  }

  out << "No se encontro camino\n";
}

void DFS(Grafo& grafo, int inicio, int final, std::ofstream& out) {
  std::stack<Node*> pila;
  std::unordered_set<int> visitados;
  std::unordered_set<int> generados;
  std::unordered_set<int> inspect;

  pila.push(new Node(inicio, nullptr, 0));
  visitados.insert(inicio);
  while (!pila.empty()) {
    Node* actual = pila.top();
    pila.pop();
    inspect.insert(actual->ID());

    if (actual->ID() == final) {
      // Hemos encontrado un camino
      Node* nodo = actual;
      out << "Camino encontrado: ";
      while (nodo != nullptr) {
        out << nodo->ID() << " ";
        nodo = nodo->GetFather();
      }
      
      out << "\nNodos visitados: ";
      for (auto &i : inspect) {
        out << i << " ";
      }

      out << "\nNodos generados: ";
      for (auto &i : generados) {
        out << i << " ";
      }      
      
      out << std::endl;
      out << "Costo total: " << actual->Cost() << std::endl;
      return;
    }

    for (const auto& vecino : grafo.nodes[actual->ID()]) {
      int nodoVecino = vecino.first;
      int costoArista = vecino.second;
      generados.insert(nodoVecino);

      if (visitados.find(nodoVecino) == visitados.end()) {
        visitados.insert(nodoVecino);
        pila.push(new Node(nodoVecino, actual, actual->Cost() + costoArista));
      }
    }
  }

  // No se encontró un camino
  out << "No se encontró un camino entre " << inicio << " y " << final << std::endl;
}


void MODBFS(Grafo& grafo, int inicio, int final, std::ofstream& out) {
  std::queue<Node*> cola;
  std::unordered_set<int> visitados;
  std::unordered_set<int> generados;
  std::unordered_set<int> inspect;
  std::default_random_engine generator; // Generador de números aleatorios
  std::uniform_real_distribution<double> distribution(0.0, 1.0); // Distribución uniforme
  
  cola.push(new Node(inicio, nullptr, 0));
  visitados.insert(inicio);
  
  while (!cola.empty()) {
    // Elegir al azar uno de los dos mejores nodos de la frontera
    int numNodosFrontera = cola.size();
    int seleccion = (distribution(generator) < 0.5) ? 0 : 1;
    for (int i = 0; i < numNodosFrontera; ++i) {
      Node* actual = cola.front();
      cola.pop();
      inspect.insert(actual->ID());
      if (i == seleccion || numNodosFrontera == 1) {
        if (actual->ID() == final) {
          // Hemos encontrado un camino
          Node* nodo = actual;
          out << "Camino encontrado: ";
          while (nodo != nullptr) {
            out << nodo->ID() << " ";
            nodo = nodo->GetFather();
          }

          out << "\nNodos visitados: ";
          for (auto &i : inspect) {
            out << i << " ";
          }

          out << "\nNodos generados: ";
          for (auto &i : generados) {
            out << i << " ";
          }
          
          
          out << std::endl;
          out << "Costo total: " << actual->Cost() << std::endl;
          return;
        }

        for (const auto& vecino : grafo.nodes[actual->ID()]) {
          int nodoVecino = vecino.first;
          int costoArista = vecino.second;
          generados.insert(nodoVecino);

          if (visitados.find(nodoVecino) == visitados.end()) {
            visitados.insert(nodoVecino);
            cola.push(new Node(nodoVecino, actual, actual->Cost() + costoArista));
          }
        }
      } else {
        // Agregar el nodo no seleccionado nuevamente a la cola
        cola.push(actual);
      }
    }
  }

  // No se encontró un camino
  out << "No se encontró un camino entre " << inicio << " y " << final << std::endl;
}
