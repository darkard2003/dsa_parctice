#include "dsu.cpp"
#include "queue.cpp"
#include "stack.cpp"

#include <fstream>
#include <iostream>

using namespace std;

class Edge {
public:
  int s;
  int d;
  int w;

  Edge() {
    s = 0;
    d = 0;
    w = 0;
  }
  Edge(int s, int d, int w) {
    this->s = s;
    this->d = d;
    this->w = w;
  }
};

class Graph {
  int **adMat;
  int v, e;

public:
  Graph() {
    adMat = NULL;
    v = 0;
    e = 0;
  }

  ~Graph() {
    for (int i = 0; i < v; i++)
      delete[] adMat[i];
    delete[] adMat;
  }

  bool loadFromFile(string filename) {
    fstream f;
    f.open(filename);
    if (!f.is_open()) {
      return false;
    }
    f >> v;
    adMat = new int *[v];
    int c = 0;
    for (int i = 0; i < v; i++) {
      adMat[i] = new int[v];
      for (int j = 0; j < v; j++) {
        f >> adMat[i][j];
        if (adMat[i][j])
          c++;
      }
    }
    e = c / 2;
    return true;
  }

  int noVertex() { return v; }
  int noEdge() { return e; }

  void dfs() {
    bool *visited = new bool[v]{false};
    Stack s(v);

    s.push(0);
    visited[0] = true;

    while (!s.isEmpty()) {
      int c = s.pop();
      cout << c << " ";

      for (int i = 0; i < v; i++) {
        if (adMat[c][i] && !visited[i])
          s.push(i), visited[i] = true;
      }
    }
    cout << endl;
    delete[] visited;
  }

  void bfs() {
    bool *visited = new bool[v]{false};
    Queue q(v);
    q.enqueue(0);
    visited[0] = true;
    while (!q.isEmpty()) {
      int c = q.dequeue();
      cout << c << " ";
      for (int i = 0; i < v; i++)
        if (adMat[c][i] && !visited[i])
          q.enqueue(i), visited[i] = true;
    }
    delete[] visited;
  }

  Edge *getEdgeList() {
    Edge *edgeList = new Edge[e];
    int c = 0;
    for (int i = 0; i < v; i++)
      for (int j = i; j < v; j++)
        if (adMat[i][j]) {
          edgeList[c++] = Edge(i, j, adMat[i][j]);
        }
    return edgeList;
  }

  void sortEdges(Edge *edges, int n) {
    for (int i = n - 2; i > 0; i--) {
      bool sorted = true;
      for (int j = 0; j <= i; j++)
        if (edges[j].w > edges[j + 1].w)
          swap(edges[j], edges[j + 1]), sorted = false;
      if (sorted)
        break;
    }
  }

  void kruskalsMST() {
    Edge *edges = getEdgeList();
    sortEdges(edges, e);

    Edge *mst = new Edge[e];
    int c = -1;

    DSU dsu(e);

    int w = 0;

    for (int i = 0; i < e; i++) {
      Edge e = edges[i];
      if (dsu.join(e.s, e.d)) {
        mst[++c] = e;
        w += e.w;
      }
    }

    for (int i = 0; i <= c; i++) {
      Edge e = mst[i];
      cout << e.s << "->" << e.d << " : " << e.w << endl;
    }
    cout << "Total Weight :: " << w;

    delete[] edges;
  }
};
