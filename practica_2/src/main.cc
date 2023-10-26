#include <iostream>
#include <fstream>

#include "maze.h"

int main(int argc, char* argv[]) {
  std::ifstream file(argv[1]);
  Maze maze(file);
  maze.Resolve(true);
  maze.PrintNM();

  int choice;
  while (true) {
    std::cout << "========== Menu ==========\n";
    std::cout << "1. Seleccionar Heuristica.\n";
    std::cout << "2. Cambiar nodo de arranque y final.\n";
    std::cout << "3. Salir.\n";

    std::cin >> choice;
    bool isManhattan = true;
    if (choice == 1) {
      int election;
      std::cout << "Distancia de Manhattan[1]\n";
      std::cout << "Euclidean[2]\n";
      std::cin >> election;

      maze.ResetM();
      switch (election) {
      case 1:
        maze.Resolve(true);

        break;
      case 2: 
        maze.Resolve(false);

        break;
      default:
        break;
      }

      maze.PrintNM();
      
    } else if (choice == 2) {
      maze.ResetM();
      int x, y;
      std::cout << "Introduzca las coordenadas del nodo de arranque: ";
      std::cin >> x >> y;
      maze.SetNewStart(x,y);

      std::cout << "Introduzca las coordenadas del nodo final: ";
      std::cin >> x >> y;
      maze.SetNewEnd(x,y);

      maze.Resolve(isManhattan);
      maze.PrintNM();

    } else {
      exit(1);
    }
    
  }
  //maze.Resolve();
  //maze.PrintNM();

  return 0;
}