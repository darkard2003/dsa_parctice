#include <iostream>
using namespace std;

int _binSearch(int k, int *arr, int l, int r) {
  if (l > r)
    return -1;
  int m = (l + r) / 2;
  if (arr[m] == k)
    return m;
  if (k > arr[m])
    return _binSearch(k, arr, m + 1, r);
  return _binSearch(k, arr, l, m - 1);
}

int bsearch(int k, int *arr, int n) { return _binSearch(k, arr, 0, n - 1); }

void bsort(int *arr, int n) {
  for (int i = n - 1; i > 0; i--)
    for (int j = 0; j < i; j++)
      if (arr[j] > arr[j + 1])
        swap(arr[j], arr[j + 1]);
}

int main() {
  int *arr, n, k;
  cout << "Enter the size:: ";
  cin >> n;
  arr = new int[n];
  cout << "Enter the elements:: ";
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  cout << "Sorting array:: " << endl;
  bsort(arr, n);
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  cout << endl << "Enter the search key:: ";
  cin >> k;
  int res = bsearch(k, arr, n);
  if (res == -1)
    cout << "Result not found" << endl;
  else
    cout << "Result found at pos " << res;
}
