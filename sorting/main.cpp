#include <iostream>

using namespace std;

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}
void test_sort(void (*sort)(int *, int)) {
  int arr[] = {5, 4, 3, 2, 1};
  int n = sizeof(arr) / sizeof(arr[0]);
  sort(arr, n);
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  cout << endl;

  int arr2[] = {1, 2, 3, 4, 5};
  int n2 = sizeof(arr2) / sizeof(arr2[0]);
  sort(arr2, n2);
  for (int i = 0; i < n2; i++)
    cout << arr2[i] << " ";
  cout << endl;

  int arr3[] = {1, 2, 3, 5, 4};
  int n3 = sizeof(arr3) / sizeof(arr3[0]);
  sort(arr3, n3);
  for (int i = 0; i < n3; i++)
    cout << arr3[i] << " ";
  cout << endl;
}

void bubbleSort(int *arr, int n) {
  for (int i = n - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (arr[j] > arr[j + 1])
        swap(arr[j], arr[j + 1]);
    }
  }
}

void seSort(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    int minIdx = i;
    for (int k = minIdx + 1; k < n; k++) {
      if (arr[k] < arr[minIdx])
        minIdx = k;
    }
    if (arr[minIdx] < arr[i])
      swap(arr[minIdx], arr[i]);
  }
}

void isort(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int e = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > e) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = e;
  }
}

int parition(int *arr, int l, int r) {
  int pivot = arr[r - 1];
  int i = l;
  for (int j = l; j < r; j++) {
    if (arr[j] < pivot) {
      swap(arr[i++], arr[j]);
    }
  }
  swap(arr[i], arr[r - 1]);
  return i;
}

void _qsort(int *arr, int l, int r) {
  if (l >= r)
    return;
  int p = parition(arr, l, r);
  _qsort(arr, l, p);
  _qsort(arr, p + 1, r);
}

void merge(int *arr, int l, int m, int r) {
  int i = l, j = 0, k = 0;
  int lsize = m - l + 1;
  int rsize = r - m;
  int *larr = new int[lsize];
  int *rarr = new int[rsize];
  while (i <= m) {
    larr[j++] = arr[i++];
  }
  while (i <= r) {
    rarr[k++] = arr[i++];
  }
  i = l;
  j = 0;
  k = 0;
  while (i <= r && j < lsize && k < rsize) {
    if (larr[j] < rarr[k])
      arr[i++] = larr[j++];
    else
      arr[i++] = rarr[k++];
  }
  while (j < lsize) {
    arr[i++] = larr[j++];
  }
  while (k < rsize) {
    arr[i++] = rarr[k++];
  }
}

void _msort(int *arr, int l, int r) {
  if (l >= r)
    return;
  int m = (l + r) / 2;
  _msort(arr, l, m);
  _msort(arr, m + 1, r);
  merge(arr, l, m, r);
}

void qsort(int *arr, int n) { _qsort(arr, 0, n); }
void msort(int *arr, int n) { _msort(arr, 0, n - 1); }

int main() {
  cout << "bubbleSort" << endl;
  test_sort(bubbleSort);

  cout << "se sort" << endl;
  test_sort(seSort);

  cout << "isort" << endl;
  test_sort(isort);

  cout << "qsort" << endl;
  test_sort(qsort);

  cout << "msort" << endl;
  test_sort(msort);

  return 0;
}
