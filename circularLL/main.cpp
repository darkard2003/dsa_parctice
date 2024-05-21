#include <iostream>
using namespace std;


class Node{
public:
  int data;
  Node *next;

  Node(){
    data = 0;
    next = NULL;
  }

  Node(int data){
    this->data = data;
    next = NULL;
  }
};

class CLL{
private:
  Node *head;
public:
  CLL(){
    head = NULL;
  }

  void insertBigining(int data){
    Node *nn = new Node(data);
    if(head == NULL){
      head = nn;
      nn->next = head;
      return;
    }
    nn->next = head->next;
    head->next = nn;
  }

  void insertEnd(int data){
    Node *nn = new Node(data);
    if(head == NULL){
      head = nn;
      nn->next = head;
      return;
    }

    nn->next = head->next;
    head->next = nn;
    head = nn;
  }

  void display(){
    if(head==NULL){
      cout << "Empty Linked List" << endl;
      return;
    }
    Node *temp = head;
    do{
      temp = temp->next;
      cout << temp->data << " ";
    }while(temp != head);
    cout << endl;
  }

};

int main(){
  CLL cll;
  int d, c;

  do{
    cout << "1. Insert Bigining" << endl
         << "2. Insert End" << endl
         << "3. Display" << endl
         << "0. Exit" << endl
         << "Enter your choice:: ";
    cin >> c;

    switch(c){
      case 1:
        cout << "Enter the data :: ";
        cin >> d;
        cll.insertBigining(d);
        break;
      case 2:
        cout << "Enter the data :: ";
        cin >> d;
        cll.insertEnd(d);
        break;
      case 3:
        cll.display();
        break;
      case 0:
        break;
      default:
        cout << "Ivalid choice" << endl;
    }
  }while(c!=0);

  return 0;
}

