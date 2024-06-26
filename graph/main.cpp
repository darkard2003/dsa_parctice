#include "graph.cpp"
#include <iostream>

using namespace std;

void dfsBfsTest() {
  Graph g;
  g.loadFromFile("graph.txt");
  cout << "Edges :: " << g.noEdge() << endl
       << "Vertex :: " << g.noVertex() << endl;

  g.dfs();
  g.bfs();
}

void mstTest() {
  Graph g;
  bool res = g.loadFromFile("wgraph.txt");
  if (!res)
    cout << "Falid to load file";
  g.kruskalsMST();
  g.primsMST();
}

void colorTest() {
  Graph g;
  g.loadFromFile("graph.txt");
  g.mcolor(3);
}

void pathTest() {
  Graph g;
  g.loadFromFile("wdag.txt", true);
  g.froydWarshall();
}

int main() {
  colorTest();
  return 0;
}
