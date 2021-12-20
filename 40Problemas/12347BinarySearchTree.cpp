#include<bits/stdc++.h>
using namespace std;
#include <queue>
#define ll long long

struct Node{
  int data;
  struct Node *left, *right;
};

Node* newNode(int data){
  Node *temp = new Node;
  temp->data = data;
  temp->left = temp->right = NULL;
  return temp;
}

//Apartir del preorden construye recursivamente el arbol
struct Node* construyeBST(int preorden[], int inicio, int fin){
  if (inicio >  fin)
    return NULL;

  struct Node* node = newNode(preorden[inicio]);

  int i;
  for(i = inicio; i<= fin; i++){
    if(preorden[i] > node->data)
      break;
  }

  node->left = construyeBST(preorden, inicio + 1, i - 1);
  node->right = construyeBST(preorden, i, fin);

  return node;

}
//Dada la raiz imprime el arbol en postorden recursivamente
void Postorden(Node* &current){
    if (current->left!=NULL)
        Postorden(current->left);

    if (current->right!=NULL)
       Postorden(current->right);

    cout << current->data << '\n';
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a;
  queue<int> datos;

  while (cin>>a) {
    datos.push(a);
  }

  int tam = datos.size();
  int A[tam];

  //Agregamos los datos en un arreglo
  for(int i = 0; i < tam; i++){
    A[i] = datos.front();
    datos.pop();
  }

  struct Node* root = construyeBST(A, 0, tam-1);

  //Imprimimos en Postorden
  Postorden(root);

  return 0;
}
