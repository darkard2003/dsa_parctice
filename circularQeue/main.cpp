#include<iostream>

using namespace std;

class CircularQeue{
  int *arr;
  int front;
  int back;
  int max;

public:
  CircularQeue(int size){
    max = size;
    arr = new int[size];
    front = 0;
    back = 0;
  }

  bool isEmpty(){
    return front == back;
  }

  int next(){
    return (front + 1)%max;
  }

  bool isFull(){
    return next() == back;
  }

  void enqeue(int data){
    if(isFull()){
      cout << "Qeue is full" << endl;
      return;
    }
    front = next();
    arr[front] = data;
  }

  int deqeue(){
    if(isEmpty()){
      cout << "Qeue is empty" << endl;
      return -1;
    }

    return arr[++back];
  }
};

int main(){
  int size;
  cout << "Enter size";
  cin >> size;
  CircularQeue cq(size);
  int d, c;

  do{
    cout << "1. Enqeue" << endl
         << "2. Deqeue" << endl
         << "0. Exit" << endl
         << "Enter your choice :: ";
    cin >> c;

    switch(c){
      case 1:
        cout << "Enter your value :: ";
        cin >> d;
        cq.enqeue(d);
        break;
      case 2:
        d = cq.deqeue();
        cout << "Popped " << d << endl;
        break;
      case 0:
        break;
      default:
        cout << "Invalid Choice" << endl;
    }
  }while(c!=0);
}
