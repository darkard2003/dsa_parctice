class Queue {
  int *arr;
  int n, l, r;

public:
  Queue(int n) {
    arr = new int[n];
    this->n = n;
    l = -1;
    r = -1;
  }

  ~Queue() { delete[] arr; }

  bool isFull() { return r == n - 1; }
  bool isEmpty() { return l == r; }
  void enqueue(int x) { arr[++r] = x; }
  int dequeue() { return arr[++l]; }
};
