#include<iostream>
using namespace std;

int search(int *arr, int n, int k){
  for(int i=0; i<n; i++){
    if(arr[i] == k)
      return i;
  }
  return -1;
}

int main(){
  int max;
  cout << "Enter the max size :: ";
  cin >> max;

  int *arr = new int[max];
  for(int i=0; i<max; i++){
    arr[i] = 0;
  }

  int k, v, res;
  int c;

  do{
    cout << "1. Update" << endl
         << "2. Insert" << endl
         << "3. Search" << endl
         << "4. Remove" << endl
         << "5. Display"<< endl
         << "0. Exit"   << endl
         << "Enter your choice :: ";
    cin >> c;
    switch(c){
case 1:
  cout << "Enter the key and value:: ";
  cin >> k >> v;
  if(k < 0 || k >= max){
    cout << "Enter a valid position";
    break;
  }
  arr[k] = v;
  break;
case 2:
  cout << "Enter the key and value:: ";
  cin >> k >> v;
  if(k < 0 || k >= max){
    cout << "Enter a valid position";
    break;
  }
  arr[k] = v;
  break;
case 3:
    cout << "Enter the value:: ";
    cin >> v;
    res = search(arr, max, v);
    if(res == -1){
      cout << "Element not found" << endl;
      break;
    }
    cout << "Element found at pos " << res << endl;
    break;
case 4:
    cout << "Enter the value to remove:: ";
    cin >> v;
    res = search(arr, max, v);
    if(res == -1){
      cout << "Element not found";
      break;
    }
    for(int i=res; i<max-1; i++){
      arr[i] = arr[i+1];
    }
    break;
case 5:
    for(int i=0; i<max; i++){
      cout << arr[i] << "\t"; 
    }
    cout << endl;
    break;
case 0:
    break;
default:
    cout << "Enter a valid choice" << endl;
    }
  }while(c!=0);
}

