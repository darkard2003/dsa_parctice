class DSU {
  int *arr;
  int n;

public:
  DSU(int n) {
    arr = new int[n];
    this->n = n;
    for (int i = 0; i < n; i++)
      arr[i] = -1;
  }

  ~DSU() { delete[] arr; }

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
