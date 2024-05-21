#include <iostream>
using namespace std;

int max(int a, int b) { return a > b ? a : b; }

class Node
{
public:
  Node *rchild;
  Node *lchild;
  int data;
  int height;

  Node()
  {
    rchild = NULL;
    lchild = NULL;
    data = 0;
    height = 1;
  }

  Node(int data)
  {
    rchild = NULL;
    lchild = NULL;
    this->data = data;
    height = 1;
  }
};

int _newHeight(Node *root)
{
  if (root == NULL)
    return 0;
  return max(_newHeight(root->lchild), _newHeight(root->rchild)) + 1;
}

int _height(Node *root)
{
  if (root == NULL)
    return 0;
  return root->height;
}

Node *rightRotate(Node *root)
{
  Node *l = root->lchild;
  Node *lr = l->rchild;

  l->rchild = root;
  root->lchild = lr;

  root->height = _newHeight(root);
  l->height = _newHeight(l);

  return l;
}

Node *leftRotate(Node *root)
{
  Node *r = root->rchild;
  Node *rl = r->lchild;

  r->lchild = root;
  root->rchild = rl;

  root->height = _newHeight(root);
  r->height = _newHeight(r);

  return r;
}

Node *_insert(Node *root, int data)
{
  if (root == NULL)
  {
    Node *nn = new Node(data);
    return nn;
  }

  if (data > root->data)
    root->rchild = _insert(root->rchild, data);
  else if (data < root->data)
    root->lchild = _insert(root->lchild, data);
  else
    return root;

  root->height = _newHeight(root);
  int balance = _height(root->lchild) - _height(root->rchild);

  if (balance < -1)
  {
    if (data > root->rchild->data)
    {
      return leftRotate(root);
    }
    root->rchild = rightRotate(root->rchild);
    return leftRotate(root);
  }
  if (balance > 1)
  {
    if (data < root->lchild->data)
    {
      return rightRotate(root);
    }
    root->lchild = leftRotate(root->lchild);
    return rightRotate(root);
  }

  return root;
}

void _inorder(Node *root)
{
  if (root == NULL)
    return;
  _inorder(root->lchild);
  cout << root->data << " ";
  _inorder(root->rchild);
}

void _preorder(Node *root)
{
  if (root == NULL)
    return;
  cout << root->data << " ";
  _preorder(root->lchild);
  _preorder(root->rchild);
}

void _postorder(Node *root)
{
  if (root == NULL)
    return;
  _postorder(root->lchild);
  _postorder(root->rchild);
  cout << root->data << " ";
}

class AVL
{
  Node *root;

public:
  AVL() { root = NULL; }

  void insert(int data) { root = _insert(root, data); }
  void inorder() { _inorder(root); }
  void preorder() { _preorder(root); }
  void postorder() { _postorder(root); }
};

int main()
{
  AVL avl;
  int choice, value;

  while (true)
  {
    cout << "\n1. Insert" << endl;
    cout << "2. In-order traversal" << endl;
    cout << "3. Pre-order traversal" << endl;
    cout << "4. Post-order traversal" << endl;
    cout << "5. Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter the value to insert: ";
      cin >> value;
      avl.insert(value);
      break;
    case 2:
      cout << "In-order traversal: ";
      avl.inorder();
      break;
    case 3:
      cout << "Pre-order traversal: ";
      avl.preorder();
      break;
    case 4:
      cout << "Post-order traversal: ";
      avl.postorder();
      break;
    case 5:
      return 0;
    default:
      cout << "Invalid choice. Please choose a valid option." << endl;
    }
  }

  return 0;
}