#include <iostream>

using namespace std;

int mt[100][100];
int kt[100][100];

void printPairs(int i, int j) {
  if (i == j) {
    cout << "A" << i;
    return;
  }
  cout << "(";
  printPairs(i, kt[i][j]);
  printPairs(kt[i][j] + 1, j);
  cout << ")";
}

int getMatChan(int *p, int n, int i, int j) {
  if (i == j)
    return 0;

  if (mt[i][j] != -1)
    return mt[i][j];

  mt[i][j] = INT_MAX;

  for (int k = i; k < j; k++) {
    int val = getMatChan(p, n, i, k) + getMatChan(p, n, k + 1, j) +
              p[i - 1] * p[k] * p[j];
    if (val < mt[i][j])
      mt[i][j] = val, kt[i][j] = k;
  }
  return mt[i][j];
}

void printMat(int mat[100][100], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << mat[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}

int main() {
  memset(mt, -1, sizeof mt);
  memset(kt, 0, sizeof kt);

  int n;
  cout << "Enter the number of matricies :: ";
  cin >> n;
  int *p = new int[++n];
  cout << "Enter " << n << " number of values:: ";
  for (int i = 0; i < n; i++)
    cin >> p[i];

  int m = getMatChan(p, n, 1, n-1);

  cout << "Mtable :: " << endl;
  printMat(mt, n);

  cout << "Ktable :: " << endl;
  printMat(kt, n);

  cout << "Mul required :: " << m << endl;
  printPairs(1, n-1);
  return 0;
}
