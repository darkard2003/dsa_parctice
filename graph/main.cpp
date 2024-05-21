#include "graph.cpp"
#include <iostream>

using namespace std;

int main() {
  Graph g;
  g.loadFromFile("graph.txt");
  cout << "Edges :: " << g.noEdge() << endl
       << "Vertex :: " << g.noVertex() << endl;

  g.dfs();
  g.bfs();
}
