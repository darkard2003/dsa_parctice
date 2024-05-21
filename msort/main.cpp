#include <iostream>

using namespace std;

void merge(int *arr, int l, int m, int r) {
  int n = r - l + 1;
  int *aux = new int[n];
  int i = l, j = m + 1, k = 0;

  while (k < n && i <= m && j <= r) {
    if (arr[i] < arr[j])
      aux[k++] = arr[i++];
    else
      aux[k++] = arr[j++];
  }

  while (k < n && i <= m)
    aux[k++] = arr[i++];
  while (k < n && j <= r)
    aux[k++] = arr[j++];

  for (int i = 0; i < n; i++)
    arr[l + i] = aux[i];

  delete[] aux;
}

void msort(int *arr, int l, int r) {
  if (l >= r)
    return;
  int m = (l + r) / 2;
  msort(arr, l, m);
  msort(arr, m + 1, r);
  merge(arr, l, m, r);
}

void msort(int *arr, int n) { msort(arr, 0, n - 1); }

void printArr(int *arr, int n) {
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main() {
  int *arr, n;
  cout << "Enter the size:: ";
  cin >> n;

  arr = new int[n];
  cout << "Enter the elements:: ";
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  msort(arr, n);
  printArr(arr, n);

  delete[] arr;
  return 0;
}
