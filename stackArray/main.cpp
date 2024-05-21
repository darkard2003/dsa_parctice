#include<iostream>
using namespace std;

class Stack{
  int *arr;
  int top;
  int max;
public:
  Stack(int size){
    arr = new int[size];
    max = size;
    top = -1;
  }

  bool isFull() {return top == max-1;}
  bool isEmpty() {return top == -1;}

  void peek(){
    if(isEmpty()){
      cout << "Stack is empty" << endl;
      return;
    }
    cout << "Top :: " << arr[top];
  }

  void push(int item){
    if(isFull()){
      cout << "Stack Overflow" << endl;
      return;
    }
    arr[++top] = item;
    cout << item << " Inserted at top" << endl;
  }

  int pop(){
    if(isEmpty()){
      cout << "Stack Underflow" << endl;
      return -1;
    }
    int item = arr[top--];
    cout << "Popped " << item << endl;
    return item;
  }

  void display(){
    if(isEmpty()){
      cout << "Stack is empty" << endl;
      return;
    }

    for(int i=0; i<=top; i++){
      cout << arr[i] << "\t";
    }
    cout << endl;
  }
};


int main(){
  int size;
  cout << "Enter the size :: ";
  cin >> size;

  Stack s(size);
  int v, c;

  do{
    cout << "1. isFull" << endl
         << "2. isEmpty" << endl
         << "3. peek" << endl
         << "4. push"<<endl
         << "5. pop" << endl
         << "6. display" << endl
         << "0. Exit" << endl
         << "Enter your choice :: ";
    cin >> c;
    switch(c){
      case 1:
        if(s.isFull()){
          cout << "Stack is full";
        } else{
          cout << "Stack is not full";
        }
        cout << endl;
        break;
      case 2:
        if(s.isEmpty()){
          cout << "Stack is empty";
        } else{
          cout << "Stack is not empty";
        }
        cout << endl;
        break;
      case 3:
        s.peek();
        break;
      case 4:
        cout << "Enter the element :: ";
        cin >> v;
        s.push(v);
        break;
      case 5:
        s.pop();
        break;
      case 6:
        s.display();
        break;
      case 0:
        break;
      default:
        cout << "Invalid coice" << endl;
    }
  } while(c!=0);

  return 0;
}
