class Stack {
  int *arr;
  int n;
  int t;

public:
  Stack(int n) {
    arr = new int[n];
    this->n = n;
    t = -1;
  }

  ~Stack() { delete[] arr; }

  bool isFull() { return t == n - 1; }
  bool isEmpty() { return t == -1; }

  bool push(int x) {
    if (isFull())
      return false;
    arr[++t] = x;
    return true;
  }

  int pop() {
    if (isEmpty())
      return -1;
    return arr[t--];
  }
};
