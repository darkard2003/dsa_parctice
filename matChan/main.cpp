#include <iostream>

using namespace std;

int dp[100][100];

int matChanMemoised(int *p, int i, int j) {
  if (i == j)
    return 0;

  if (dp[i][j] != -1)
    return dp[i][j];

  dp[i][j] = INT_MAX;
  for (int k = i; k < j; k++) {
    dp[i][j] =
        min(dp[i][j], matChanMemoised(p, i, k) + matChanMemoised(p, k + 1, j) +
                          p[i - 1] * p[k] * p[j]);
  }

  return dp[i][j];
}

int matChanMemoised(int *p, int n) { return matChanMemoised(p, 0, n - 1); }

void printMat(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << dp[i][j] << " ";
    cout << endl;
  }
}

int main() {
  int arr[] = {1, 3, 4, 5};
  int n = sizeof(arr) / sizeof(arr[0]);
  memset(dp, -1, sizeof dp);
  cout << "Multiplicaiton required " << matChanMemoised(arr, n) << endl;
  printMat(n);
  cout << endl;
}
