#include <fstream>
#include <iostream>

using namespace std;

class Edge {
public:
  int s, d, w;
  Edge(int s, int d, int w) {
    this->s = s;
    this->d = d;
    this->w = w;
  }
  Edge() {
    this->s = 0;
    this->d = 0;
    this->w = 0;
  }
};

class DSU {
  int *arr;

public:
  DSU(int n) {
    arr = new int[n];
    for (int i = 0; i < n; i++) {
      arr[i] = -1;
    }
  }

  int find(int x) {
    if (arr[x] == -1)
      return x;
    return arr[x] = find(arr[x]);
  }

  bool join(int a, int b) {
    int x = find(a);
    int y = find(b);
    if (x == y)
      return false;
    arr[x] = y;
    return true;
  }
};

class Graph {
  int V, e, **graph;
  bool isDirected;

public:
  bool loadFromFile(string filename, bool isDirected = false) {
    this->isDirected = isDirected;
    int c = 0;

    fstream f;
    f.open(filename);

    if (!f.is_open())
      return false;

    f >> V;
    graph = new int *[V];
    for (int i = 0; i < V; i++) {
      graph[i] = new int[V];
      for (int j = 0; j < V; j++) {
        f >> graph[i][j];
        if (graph[i][j])
          c++;
      }
    }
    e = isDirected ? c : c / 2;
    f.close();

    return true;
  }

  Edge *getEdgeList() {
    Edge *edges = new Edge[e];
    int c = 0;

    for (int i = 0; i < V; i++) {
      for (int j = isDirected ? 0 : i; j < V; j++) {
        if (graph[i][j])
          edges[c++] = Edge(i, j, graph[i][j]);
      }
    }
    if (c != e)
      cout << "Edges length doesnt math" << endl;
    return edges;
  }

  void sortEdges(Edge *edges, int n) {
    for (int i = n - 1; i >= 0; i--) {
      bool sorted = true;
      for (int j = 0; j < i; j++) {
        if (edges[j].w > edges[j + 1].w)
          swap(edges[j], edges[j + 1]), sorted = false;
        if (sorted)
          break;
      }
    }
  }

  void kruskal() {
    Edge *edges = getEdgeList();
    sortEdges(edges, e);
    Edge *mstList = new Edge[e];
    int c = 0;
    int w = 0;

    DSU dsu(e);

    for (int i = 0; i < e; i++) {
      Edge edge = edges[i];
      if (dsu.join(edge.s, edge.d)) {
        mstList[c++] = edge;
        w += edge.w;
      }
    }

    cout << "Edge\tWeight" << endl;
    for (int i = 0; i < c; i++)
      cout << edges[i].s << " -> " << edges[i].d << "\t" << edges[i].w << endl;
    cout << "Total Weight:: " << w << endl;
  }

  int minKey(int *keys, bool *visited) {
    int minKey = INT_MAX, minIdx = -1;
    for (int i = 0; i < V; i++)
      if (!visited[i] && keys[i] < minKey)
        minKey = keys[i], minIdx = i;
    return minIdx;
  }

  void prims() {
    bool *mstSet = new bool[V]{false};
    int *keys = new int[V];
    int *parent = new int[V];
    for (int i = 0; i < V; i++)
      keys[i] = INT_MAX, parent[i] = -1;
    keys[0] = 0;

    for (int i = 0; i < V - 1; i++) {
      int u = minKey(keys, mstSet);
      mstSet[u] = true;
      for (int v = 0; v < V; v++) {
        if (graph[u][v] && !mstSet[v] && graph[u][v] < keys[v])
          keys[v] = graph[u][v], parent[v] = u;
      }
    }
    int w = 0;
    cout << "Edge\tWeight" << endl;
    for (int i = 1; i < V; i++) {
      cout << parent[i] << "->" << i << "\t" << keys[i] << endl;
      w += keys[i];
    }

    cout << "Total Weight:: " << w << endl;

    delete[] keys;
    delete[] parent;
    delete[] mstSet;
  }

  void printPath(int *parent,  int i) {
    if (parent[i] == -1) {
      cout << i<< " ";
      return;
    }
    printPath(parent, parent[i]);
    cout << "->" << i << " ";
  }

  void djkastra() {
    bool *mstSet = new bool[V]{false};
    int *keys = new int[V];
    int *parent = new int[V];
    for (int i = 0; i < V; i++)
      keys[i] = INT_MAX, parent[i] = -1;
    keys[0] = 0;

    for (int i = 0; i < V - 1; i++) {
      int u = minKey(keys, mstSet);
      mstSet[u] = true;
      for (int v = 0; v < V; v++) {
        if (graph[u][v] && !mstSet[v] && keys[u] + graph[u][v] < keys[v])
          keys[v] = graph[u][v] + keys[u], parent[v] = u;
      }
    }

    cout << "Path\tWeight" << endl;
    for (int i = 1; i < V; i++) {
      printPath(parent, i);
      cout << "\t" << keys[i] << endl;
    }

    delete[] keys;
    delete[] parent;
    delete[] mstSet;
  }
};

int main() {
  Graph g;
  if (!g.loadFromFile("wgraph.txt")) {
    cout << "Faild to open the file" << endl;
  }
  cout << "File opened" << endl;

  cout << "Kruskal::\n";
  g.kruskal();
  cout << endl;
  cout << "Prims:: \n";
  g.prims();

  cout << endl;

  cout << "DJkastra" << endl;
  g.djkastra();
  return 0;
}
