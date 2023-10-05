/**
 * 
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Curso: 3ro
 * 
 * @category Inteligencia Artificial
 * @file main.cc
 * @brief  
 * @author Eric Angueta Rogel || alu0101335339@ull.edu.es
 * @version 0.1
 * @date 26-09-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <fstream>
#include "../include/grafo.h"

int main(int argc, char* argv[]) {

  std::string name{argv[1]};
  std::fstream file(name);
  std::ofstream out("resultados.txt");
  
  std::string aux;
  std::getline(file, aux);
  Grafo graph(stoi(aux));
  
  for (size_t i = 1; i <= graph.vertices;  ++i) {
    for (size_t j = i + 1; j <= graph.vertices; ++j) {
      std::getline(file, aux);
      float cost = stof(aux);
      if (cost > -1) graph.AddEdge(i, j, cost); 
    }
  }

  //PrintGraph(graph);
  out << "Recorrido en amplitud\n";
  BFS(graph, int(stoi(std::string(argv[2]))), int(stoi(std::string(argv[3]))), out);
  out << "\nRecorrido en profundidad\n";
  DFS(graph, int(stoi(std::string(argv[2]))), int(stoi(std::string(argv[3]))), out);
  out << "\nModificacion de BFS\n";
  MODBFS(graph, int(stoi(std::string(argv[2]))), int(stoi(std::string(argv[3]))), out);
  return 0;
}

