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
  //Usage(argc, argv[]);
  std::string name{argv[1]};
  std::fstream file(name);
  
  std::string aux;
  aux = argv[2];
  int init = stoi(aux);
  aux = argv[3];
  int fin = stoi(aux);

  Grafo grafo1(file);
  grafo1.Anchura(init, fin);

  return 0;
}

