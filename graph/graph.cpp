#include "dsu.cpp"
#include "queue.cpp"
#include "stack.cpp"

#include <fstream>
#include <iostream>

using namespace std;

void printPath(int s, int d, int *parent) {
  if (s == -1)
    return;
  if (s == d) {
    cout << s;
    return;
  }
  printPath(parent[s], d, parent);
  cout << " -> " << s;
}

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
  bool isDirected;

public:
  Graph() {
    adMat = NULL;
    v = 0;
    e = 0;
    isDirected = false;
  }

  ~Graph() {
    for (int i = 0; i < v; i++)
      delete[] adMat[i];
    delete[] adMat;
  }

  bool loadFromFile(string filename, bool isDirected = false) {
    this->isDirected = isDirected;
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
    e = isDirected ? c : c / 2;
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
      for (int j = isDirected ? 0 : i; j < v; j++)
        if (adMat[i][j]) {
          edgeList[c++] = Edge(i, j, adMat[i][j]);
        }
    return edgeList;
  }

  void sortEdges(Edge *edges, int n) {
    for (int i = n - 1; i > 0; i--) {
      bool sorted = true;
      for (int j = 0; j < i; j++)
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
    cout << "Total Weight :: " << w << endl;

    delete[] edges;
  }

  int minKey(int *key, bool *mstSet) {
    int minIdx = -1, minVal = INT_MAX;
    for (int i = 0; i < v; i++)
      if (!mstSet[i] && key[i] < minVal)
        minVal = key[i], minIdx = i;
    return minIdx;
  };

  void primsMST() {
    int *key = new int[v];
    int *parent = new int[v];

    bool *mstSet = new bool[v]{false};

    for (int i = 0; i < v; i++)
      key[i] = INT_MAX, parent[i] = -1;

    key[0] = 0;

    for (int i = 0; i < v - 1; i++) {
      int m = minKey(key, mstSet);
      mstSet[m] = true;
      for (int i = 0; i < v; i++) {
        if (adMat[m][i] && !mstSet[i] && adMat[m][i] < key[i])
          key[i] = adMat[m][i], parent[i] = m;
      }
    }

    cout << "Edge\t" << "Weight\n";
    int w = 0;
    for (int i = 1; i < v; i++) {
      cout << parent[i] << "->" << i << "\t" << key[i] << endl;
      w += key[i];
    }
    cout << "Total weight :: " << w << endl;

    delete[] key;
    delete[] parent;
    delete[] mstSet;
  }

  void djkastra() {
    int *key = new int[v];
    int *parent = new int[v];
    bool *visited = new bool[v]{false};
    for (int i = 0; i < v; i++)
      key[i] = INT_MAX, parent[i] = -1;
    key[0] = 0;
    for (int i = 0; i < v - 1; i++) {
      int m = minKey(key, visited);
      visited[m] = true;
      for (int j = 0; j < v; j++) {
        if (adMat[m][j] && !visited[j] && key[m] + adMat[m][j] < key[j])
          key[j] = key[m] + adMat[m][j], parent[j] = m;
      }
    }

    for (int i = 0; i < v; i++) {
      printPath(i, 0, parent);
      cout << " : " << key[i] << endl;
    }
    delete[] key;
    delete[] parent;
    delete[] visited;
  }

  void bellmanFroyd() {
    Edge *edges = getEdgeList();
    int *dist = new int[v];
    int *parent = new int[v];

    for (int i = 0; i < e; i++)
      cout << edges[i].s << "-->" << edges[i].d << " : " << edges[i].w << endl;

    for (int i = 0; i < v; i++)
      dist[i] = INT_MAX, parent[i] = -1;

    dist[0] = 0;

    for (int i = 0; i < v - 1; i++) {
      for (int j = 0; j < e; j++) {
        Edge e = edges[j];
        if (dist[e.s] != INT_MAX && dist[e.s] + e.w < dist[e.d])
          dist[e.d] = dist[e.s] + e.w, parent[e.d] = e.s;
      }
    }

    for (int j = 0; j < e; j++) {
      Edge e = edges[j];
      if (adMat[e.s][e.d] && dist[e.d] > dist[e.s] + adMat[e.s][e.d]) {
        cout << "Negetive Weight Cycle detected " << e.s << " --> " << e.d
             << endl;
        return;
      }
    }

    for (int i = 0; i < v; i++) {
      printPath(i, 0, parent);
      cout << " : " << dist[i] << endl;
    }

    delete[] edges;
    delete[] dist;
    delete[] parent;
  }
};
