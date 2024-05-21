#include<iostream>

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

class LinkedList{
  Node *head;
public:
  LinkedList(){
    head = NULL;
  }

  bool isEmpty(){
    return head == NULL;
  }

  void insertBigening(int data){
    Node *nn = new Node(data);
    if(isEmpty()){
      head = nn;
      return;
    }
    nn->next = head;
    head = nn;
  }

  void insertEnd(int data){
    Node *nn = new Node(data);
    if(isEmpty())
      head = nn;
    Node *temp = head;
    while(temp->next)
      temp = temp->next;
    temp->next = nn;
  }

  void deleteBigining(){
    if(isEmpty()) return;
    Node *temp = head;
    head = head->next;
    free(temp);
  }

  void deleteEnd(){
    if(isEmpty()) return;
    if(!head -> next){
      free(head);
      head = NULL;
      return;
    }
    Node *temp = head;
    while(temp->next->next){
      temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
  }

  void display(){
    if(isEmpty()){
      cout << "List is empty" << endl;
      return;
    }
    Node *temp = head;
    while(temp){
      cout << temp->data << " ";
      temp = temp->next;
    }
    cout << endl;
  }
};

int main(){
  LinkedList ll;
  int d, c;

  do{
    cout << "1. Insert Bigening" << endl
         << "2. Insert Ending" << endl
         << "3. Delete Bigining" << endl
         << "4. Delete Ending" << endl
         << "5. Display" << endl
         << "0. Exit" << endl
         << "Enter your choice :: ";
    cin >> c;

    switch(c){
      case 1:
        cout << "Enter your data:: ";
        cin >> d;
        ll.insertBigening(d);
        break;
      case 2:
        cout << "Enter your data:: ";
        cin >> d;
        ll.insertEnd(d);
        break;
      case 3:
        ll.deleteBigining();
        break;
      case 4:
        ll.deleteEnd();
        break;
      case 5:
        ll.display();
        break;
      case 0:
        break;
        default:
      cout << "Invalid Choice" << endl;
    }

  }while(c!=0);

  return 0;
}
