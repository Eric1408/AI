#include "maze.h"

// HEURISTIC WITH MANHATTAN DISTANCE
int Heuristic(const Node* a, const Node* b, bool isManhattan) {
  if (isManhattan) {
    return (std::abs(a->Coords().first - b->Coords().first) + 
           std::abs(a->Coords().second - b->Coords().second)) * 3;

  } else {
    int dx = std::abs(a->Coords().first - b->Coords().first);
    int dy = std::abs(a->Coords().second - b->Coords().second);

    return std::sqrt(std::pow(dx + dy, 2));
  }
}

int CalculateG(const Node* from, const Node* to) {
  int dx = std::abs(to->Coords().first - from->Coords().first);
  int dy = std::abs(to->Coords().second - from->Coords().second);

  if (dx == 1 && dy == 1) return from->GetCost() + 7;

  return from->GetCost() + 5;
}

Maze::Maze(std::ifstream& input) {
  std::string line;
  if (!input) {
    std::cerr << "No se pudo abrir el archivo\n";
  } else {
    std::getline(input, line);
    x_ = stoi(std::string(line));
    
    std::getline(input, line);
    y_ = stoi(std::string(line));
    
    int i{0},j{0};

    while (std::getline(input, line)) {
      std::vector<int> row;
      std::vector<Node*> nrow;

      for (auto c : line) {
        switch (c) {
        case '0':
          nrow.push_back(new Node(std::make_pair(i, j), ID::PATH));  
          ++j;
          break;

        case '1':
          nrow.push_back(new Node(std::make_pair(i, j), ID::WALL));
          ++j;
          break;

        case '3':
          start_ = new Node(std::make_pair(i, j), ID::START);
          nrow.push_back(start_);
          ++j;
          break;

        case '4':
          end_ = new Node(std::make_pair(i, j), ID::END);
          nrow.push_back(end_);
          ++j;
          break;

        default:
          break;
        }
      } 
      nmatrix_.push_back(nrow);
      ++i;
      j = 0;
    }
  }
}


// DISPLAY THE MATRIX ON SCREEN
void Maze::PrintNM() {
  std::cout << "n: " << x_ << std::endl;
  std::cout << "m: " << y_ << std::endl;
  std::cout << "S: " << *start_ << std::endl;
  std::cout << "E: " << *end_ << std::endl;

  for (const std::vector<Node*>& r : nmatrix_) {
    for (Node* value : r) {
      switch (value->GetID()) {
      case WALL:
        std::cout << '1';
        break;    
      case PATH:
        std::cout << '0';
        break;
      case END:
        std::cout << '4';
        break;
      case START:
        std::cout << '3';
        break;
      case SOLUTION:
        std::cout << " ";
        break;
      default:
        break;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "Coste: " << end_->GetCost() << std::endl;
  std::cout << "Visitados:\n";
  for (const Node* n : visited_) {
    std::cout << *n << " ";
  }

  std::cout << "\nGenerados:\n";
  for (const Node* m : generated_) {
    std::cout << *m << " ";
  }
  std::cout << std::endl;
}

// Method to get node neighbors
std::vector<Node*> Maze::GetNeighbors(Node* n) {
  std::vector<Node*> neighbors;

  int x = n->Coords().first;
  int y = n->Coords().second;

  int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
  int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

  for (int i = 0; i < 8; ++i) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    
    //Check that exists inside nmatrix_
    if (nx >= 0 && nx < x_ && ny >= 0 && ny < y_) {
      if (nmatrix_[nx][ny]->GetID() != ID::WALL)
        neighbors.push_back(nmatrix_[nx][ny]);
    }
  }

  return neighbors;
}

void Maze::Resolve(bool isManhattan) {
  if (AStar(isManhattan)) {
    Node* current = end_;

    while (current != nullptr) {
      if (current->GetFather() != nullptr && current->GetFather()->GetID() != ID::START) {
        current = current->GetFather();
        current->SetID(ID::SOLUTION);
      } else {
        break;
      }
    }
  } else {
    std::cout << "No hay ruta psoble\n";
  }
}

// Struct for priority queue overload
struct CompareNodes {
  bool operator()(const Node* n1, const Node* n2) const {
    return n1->GetFun() > n2->GetFun();
  }
};

// if AStar find a way return true
bool Maze::AStar(bool isManhattan) {
  std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openSet;
  
  // Set aux to check if there is a node in the priority queue
  std::unordered_set<Node*> nodesInOpenSet;
  std::vector<Node*> closedSet;

  openSet.push(start_);
  nodesInOpenSet.insert(start_);

  while (!openSet.empty())  {
    Node* current = openSet.top();
    openSet.pop();
    nodesInOpenSet.erase(current);

    if (current == end_) {
      visited_ = closedSet;
      generated_ = nodesInOpenSet;
      return true;
    }

    closedSet.push_back(current);

    for (Node* n : GetNeighbors(current)) {
      if (std::find(closedSet.begin(), closedSet.end(), n) != closedSet.end()) {
        continue;
      }

      int cost = CalculateG(current, n);
      auto it = nodesInOpenSet.find(n);
      n->SetHeur(Heuristic(n, end_, isManhattan));
      
      if (cost < n->GetCost() || it == nodesInOpenSet.end()) {
        n->SetCost(cost);
        n->SetFthr(current);
          
        if (it == nodesInOpenSet.end()) {
          openSet.push(n);
          nodesInOpenSet.insert(n);
        }
      }
    }
  }
  
  return false;
}

void Maze::SetNewStart(int x, int y) {
  start_->Reset();
  start_->SetID(ID::WALL);
  Node* newn(new Node(std::make_pair(x, y), ID::START));
  start_ = newn;
  start_->SetHeur(0);
  nmatrix_[x][y] = start_;
}

void Maze::SetNewEnd(int x, int y) {
  end_->Reset();
  end_->SetID(ID::WALL);
  Node* newn(new Node(std::make_pair(x, y), ID::END));
  end_ = newn;
  end_->SetHeur(0);
  nmatrix_[x][y] = end_;
}

void Maze::ResetM() {
  for (std::vector<Node*> n : nmatrix_) {
    for (Node* m : n) {
      if (m->GetID() == ID::SOLUTION)
        m->Reset();
    }
  }
}
