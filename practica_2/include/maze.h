#pragma once

#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>

#include "node.h"

// Definiciones de tipos para facilitar la legibilidad
typedef std::vector<std::vector<int>> matrix;
typedef std::vector<std::vector<Node*>> n_matrix;

class Maze {
public:
  // CONSTRUCTOR
  Maze(std::ifstream&); // Constructor que carga un laberinto a partir de un archivo

  // MÉTODOS PÚBLICOS
  void ResetM(); // Restablece el laberinto a su estado inicial
  void SetNewStart(int, int); // Cambia las coordenadas del nodo de inicio
  void SetNewEnd(int, int); // Cambia las coordenadas del nodo final
  void Resolve(bool); // Resuelve el laberinto utilizando el algoritmo A*
  bool AStar(bool); // Implementa el algoritmo A* para buscar un camino en el laberinto
  void PrintNM(); // Imprime el laberinto en la consola
  std::vector<Node*> GetNeighbors(Node*); // Obtiene los nodos vecinos de un nodo dado

private:
  Node* start_; // Nodo de inicio
  Node* end_; // Nodo final
  int x_; // Tamaño en la dirección X del laberinto
  int y_; // Tamaño en la dirección Y del laberinto
  n_matrix nmatrix_; // Matriz de nodos que representa el laberinto
  std::vector<Node*> visited_; // Nodos visitados durante la resolución del laberinto
  std::unordered_set<Node*> generated_; // Nodos generados durante la resolución del laberinto
};
