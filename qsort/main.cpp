#include <iostream>

using namespace std;

int lpart(int *arr, int l, int r) {
  int p = arr[r];
  int i = l - 1;
  for (int j = l; j < r; j++) {
    if (arr[j] < p)
      swap(arr[j], arr[++i]);
  }
  swap(arr[++i], arr[r]);
  return i;
}

int hpart(int *arr, int l, int r) {
  int p = arr[l];
  int i = l, j = r;
  while (1) {
    while (arr[i] < p)
      i++;
    while (arr[j] > p)
      j--;
    if (i >= j)
      return j;
    swap(arr[i], arr[j]);
  }
}

void qsort(int *arr, int l, int r, int (*part)(int *, int, int)) {
  if (l >= r)
    return;
  int p = part(arr, l, r);
  qsort(arr, l, p - 1, part);
  qsort(arr, p + 1, r, part);
}

void qsort(int *arr, int n, int (*part)(int *, int, int)) {
  return qsort(arr, 0, n - 1, part);
}

void qsort(int *arr, int n) { return qsort(arr, n, lpart); }

void printArr(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int main() {
  int *arr, *arr2, n;
  cout << "Enter the size:: ";
  cin >> n;
  arr = new int[n];
  arr2 = new int[n];
  cout << "Enter the elements:: ";
  for (int i = 0; i < n; i++)
    cin >> arr[i], arr2[i] = arr[i];
  cout << "Before sorting" << endl;
  printArr(arr, n);

  cout << "After sorting Lomutose:: " << endl;
  qsort(arr, n);
  printArr(arr, n);

  cout << "After sorting Hoare:: " << endl;
  qsort(arr2, n, hpart);
  printArr(arr2, n);

  delete[] arr;
  delete[] arr2;
  return 0;
}
