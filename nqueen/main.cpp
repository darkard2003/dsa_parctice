#include <iostream>

using namespace std;

bool isSafe(int **board, int r, int c, int n) {
  for (int i = 0; i < r; i++)
    if (board[i][c])
      return false;

  for (int i = r, j = c; i >= 0 && j >= 0; i--, j--)
    if (board[i][j])
      return false;

  for (int i = r, j = c; i >= 0 && j < n; i--, j++)
    if (board[i][j])
      return false;

  return true;
}

void printBoard(int **board, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j])
        cout << "Q ";
      else
        cout << "_ ";
    }
    cout << endl;
  }
}

void nqueen(int **board, int r, int n) {
  if (r == n) {
    printBoard(board, n);
    cout << endl;
    return;
  }

  for (int i = 0; i < n; i++) {
    if (isSafe(board, r, i, n)) {
      board[r][i] = 1;
      nqueen(board, r + 1, n);
      board[r][i] = 0;
    }
  }
}

int main() {
  int n;
  cout << "Enter the size of board :: ";
  cin >> n;

  int **board = new int *[n];
  for (int i = 0; i < n; i++) {
    board[i] = new int[n]{0};
  }

  nqueen(board, 0, n);
}
