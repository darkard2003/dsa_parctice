#include "dsu.cpp"
#include "queue.cpp"
#include "stack.cpp"

#include <fstream>
#include <iostream>

using namespace std;

#define INF 999

void printPath(int s, int d, int *parent) {
  if (s == -1) {
    cout << d;
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
  int V, e;
  bool isDirected;

public:
  Graph() {
    adMat = NULL;
    V = 0;
    e = 0;
    isDirected = false;
  }

  ~Graph() {
    for (int i = 0; i < V; i++)
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
    f >> V;
    adMat = new int *[V];
    int c = 0;
    for (int i = 0; i < V; i++) {
      adMat[i] = new int[V];
      for (int j = 0; j < V; j++) {
        f >> adMat[i][j];
        if (adMat[i][j] && adMat[i][j] != INF)
          c++;
      }
    }
    e = isDirected ? c : c / 2;
    return true;
  }

  int noVertex() { return V; }
  int noEdge() { return e; }

  void dfs() {
    bool *visited = new bool[V]{false};
    Stack s(V);

    s.push(0);
    visited[0] = true;

    while (!s.isEmpty()) {
      int c = s.pop();
      cout << c << " ";

      for (int i = 0; i < V; i++) {
        if (adMat[c][i] && !visited[i])
          s.push(i), visited[i] = true;
      }
    }
    cout << endl;
    delete[] visited;
  }

  void bfs() {
    bool *visited = new bool[V]{false};

    Queue q(V);
    q.enqueue(0);

    visited[0] = true;

    while (!q.isEmpty()) {
      int c = q.dequeue();
      cout << c << " ";
      for (int i = 0; i < V; i++)
        if (adMat[c][i] && !visited[i])
          q.enqueue(i), visited[i] = true;
    }
    delete[] visited;
  }

  Edge *getEdgeList() {
    Edge *edgeList = new Edge[e];
    int c = 0;
    for (int i = 0; i < V; i++)
      for (int j = isDirected ? 0 : i; j < V; j++)
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
    for (int i = 0; i < V; i++)
      if (!mstSet[i] && key[i] < minVal)
        minVal = key[i], minIdx = i;
    return minIdx;
  };

  void primsMST() {
    int *key = new int[V];
    int *parent = new int[V];

    bool *mstSet = new bool[V]{false};

    for (int i = 0; i < V; i++)
      key[i] = INT_MAX, parent[i] = -1;

    key[0] = 0;

    for (int i = 0; i < V - 1; i++) {
      int m = minKey(key, mstSet);
      mstSet[m] = true;
      for (int v = 0; v < V; v++) {
        if (adMat[m][v] && !mstSet[v] && adMat[m][v] < key[v])
          key[v] = adMat[m][v], parent[v] = m;
      }
    }

    cout << "Edge\t" << "Weight\n";
    int w = 0;
    for (int i = 1; i < V; i++) {
      cout << parent[i] << "->" << i << "\t" << key[i] << endl;
      w += key[i];
    }
    cout << "Total weight :: " << w << endl;

    delete[] key;
    delete[] parent;
    delete[] mstSet;
  }

  void djkastra() {
    int *key = new int[V];
    int *parent = new int[V];
    bool *visited = new bool[V]{false};
    for (int i = 0; i < V; i++)
      key[i] = INT_MAX, parent[i] = -1;
    key[0] = 0;
    for (int i = 0; i < V - 1; i++) {
      int m = minKey(key, visited);
      visited[m] = true;
      for (int j = 0; j < V; j++) {
        if (adMat[m][j] && !visited[j] && key[m] + adMat[m][j] < key[j])
          key[j] = key[m] + adMat[m][j], parent[j] = m;
      }
    }

    for (int i = 0; i < V; i++) {
      printPath(i, 0, parent);
      cout << " : " << key[i] << endl;
    }
    delete[] key;
    delete[] parent;
    delete[] visited;
  }

  void bellmanFroyd() {
    Edge *edges = getEdgeList();
    int *dist = new int[V];
    int *parent = new int[V];

    for (int i = 0; i < e; i++)
      cout << edges[i].s << "-->" << edges[i].d << " : " << edges[i].w << endl;

    for (int i = 0; i < V; i++)
      dist[i] = INT_MAX, parent[i] = -1;

    dist[0] = 0;

    for (int i = 0; i < V - 1; i++) {
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

    for (int i = 0; i < V; i++) {
      printPath(i, 0, parent);
      cout << " : " << dist[i] << endl;
    }

    delete[] edges;
    delete[] dist;
    delete[] parent;
  }

  void froydWarshall() {
    int **dist = new int *[V];
    int **parent = new int *[V];

    for (int i = 0; i < V; i++) {
      dist[i] = new int[V];
      parent[i] = new int[V];
      for (int j = 0; j < V; j++)
        dist[i][j] = adMat[i][j], parent[i][j] = -1;
    }

    cout << "Initial Matrix :: " << endl;
    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++)
        cout << dist[i][j] << " ";
      cout << endl;
    }

    cout << endl;

    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        for (int k = 0; k < V; k++) {
          if (dist[i][k] != INF && dist[k][j] != INF &&
              dist[i][j] > dist[i][k] + dist[k][j])
            dist[i][j] = dist[i][k] + dist[k][j], parent[i][j] = k;
        }
      }
    }

    cout << "Final Matrix :: " << endl;
    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++)
        cout << dist[i][j] << " ";
      cout << endl;
    }

    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        if (dist[i][j] != INF) {
          printPath(j, i, parent[i]);
          cout << " : " << dist[i][j] << endl;
        }
      }
      cout << endl;
    }
  }

  bool isSafe(int *colors, int c, int cv) {
    for (int i = 0; i < V; i++)
      if (adMat[cv][i] && colors[i] == c)
        return false;
    return true;
  }

  void mcolor(int *colors, int m, int cv) {
    if (cv == V) {
      for (int i = 0; i < V; i++)
        cout << colors[i] << " ";
      cout << endl;
      return;
    }
    for (int i = 1; i <= m; i++) {
      if (isSafe(colors, i, cv)) {
        colors[cv] = i;
        mcolor(colors, m, cv + 1);
        colors[cv] = 0;
      }
    }
  }

  void mcolor(int m) {
    int *colors = new int[V]{0};
    mcolor(colors, m, 0);
  }
};
