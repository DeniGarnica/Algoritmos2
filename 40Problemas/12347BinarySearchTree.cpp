#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct Node{
  int data;
  struct Node *left, *right, *padre;
}

Node* newNode(int data){
  Node *temp = new Node;
  temp->data = data;
  temp->left = temp->right = NULL;
  return temp;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a;
  bool primero = 1;
  int actual = 0;

  while(cin>>a){
    if(primero){
      struct Node* raiz = newNode(a);
      root->padre = raiz;
      primero = 0;
      actual = raiz;
    }else{
      if(a < actual->data){
        struct Node* temp = newNode(a);
        temp->padre = actual;
        actual->left = temp;
        actual = temp;
      }else{
        while(actual->padre->data < a || actual == root){
          actual = actual->padre;}
        if(actual->left!= NULL){
          struct Node* temp = newNode(a);
          temp->padre = actual;
          actual->right = temp;
          actual = temp;
        }else{
          actual = actual->padre;
          struct Node* temp = newNode(a);
          temp->padre = actual;
          actual->right = temp;
          actual = temp;
        }
      }
    }
  }



    return 0;
  }
