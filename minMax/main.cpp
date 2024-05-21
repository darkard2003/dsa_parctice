#include <iostream>
using namespace std;

class MinMax {
public:
  int min;
  int max;

  MinMax() {
    min = 0;
    max = 0;
  }

  MinMax(int min, int max) {
    this->min = min;
    this->max = max;
  }
};

MinMax _minMax(int *arr, int l, int r) {
  if (l >= r)
    return MinMax(arr[r], arr[r]);
  if (l == r - 1) {
    if (arr[l] < arr[r])
      return MinMax(arr[l], arr[r]);
    return MinMax(arr[r], arr[l]);
  }
  int m = (l + r) / 2;
  MinMax m1 = _minMax(arr, l, m);
  MinMax m2 = _minMax(arr, m + 1, r);
  int mn = min(m1.min, m2.min);
  int mx = max(m1.max, m2.max);
  return MinMax(mn, mx);
}

MinMax getMinMax(int *arr, int n) { return _minMax(arr, 0, n - 1); }

int main() {
  int *arr, n;
  cout << "Enter the size:: ";
  cin >> n;
  arr = new int[n];
  cout << "Enter the elements:: ";
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  MinMax m = getMinMax(arr, n);

  cout << "Min element is " << m.min << endl
       << "Max element is " << m.max << endl;
}
