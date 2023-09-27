#include "../include/grafo.h"

#include <string>

Grafo::Grafo(std::istream& ifstrm) {
  std::string line;
  std::getline(ifstrm, line);
  vertices_ = stoi(line);
  std::cout << vertices_ << std::endl;
}
