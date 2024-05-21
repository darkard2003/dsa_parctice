#include "queue.cpp"
#include "stack.cpp"

#include <fstream>
#include <iostream>

using namespace std;

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
        if (adMat[i][j] == 1)
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
};
