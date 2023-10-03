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
  
  std::string aux;
  //aux = argv[2];
  //int init = stoi(aux);
  //aux = argv[3];
  //int fin = stoi(aux);

  Inf grafo;
  std::getline(file, aux);
  int vertcs = stoi(aux);
  std::cout << vertcs << std::endl;
  grafo.vertices = vertcs;
  grafo.nodes.resize(vertcs);
  
  for (size_t i = 0; i < vertcs;  ++i) {
    for (size_t j = i + 1; j < vertcs; ++j) {
      std::getline(file, aux);
      float cost = stof(aux);
      if (cost > -1) grafo.nodes[i].emplace_back(j, cost);
    }
  }
  
  for (size_t i = 0; i < grafo.nodes.size(); ++i) {
    for (size_t j = 0; j < grafo.nodes[i].size(); ++j) {
      std::cout << i << " -> " << grafo.nodes[i][j].first << " cost = " 
                << grafo.nodes[i][j].second << std::endl;
    }
  }

  return 0;
}

