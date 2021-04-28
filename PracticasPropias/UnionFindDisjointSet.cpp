#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

struct Node{
  int data;
  int rank;
  Node* parent;
};

map<int, Node> mapa; //Con esto guardamos el nodo asociado a cada dato

void Make_set(int a){
  Node* nodo = new Node();
  nodo->data = a;
  nodo->rank = 0;
  nodo->parent = nodo;
  mapa.insert ( std::pair<int,Node>(a, *nodo) );
}

int root(int a){
  Node* nodo;
  *nodo = mapa[a];
  //std::cout << nodo->data << '\n';
  while((nodo->parent)->parent!=nodo->parent){
    nodo->parent=nodo->parent->parent;
    //std::cout << "1" << '\n';
  }
  return nodo->parent->data;
}


void Union(int a, int b){
  if(a==b){
    return;
  }else{
  int r_a=root(a);
  int r_b=root(b);
  Node* raiz_a;
  Node* raiz_b;
  *raiz_a = mapa[r_a];
  *raiz_b = mapa[r_b];

  if(raiz_a->rank > raiz_b->rank){
    Node* aux= raiz_a;
    raiz_a=raiz_b;
    raiz_b=aux;
  }else{
    raiz_a->parent = raiz_b;
    raiz_b->rank++;
  }
}
}


int main(){
  Make_set(1);
  //std::cout << root(1) << '\n';
  Make_set(2);
  //std::cout << root(2) << '\n';
  Make_set(3);
  Make_set(4);
  Make_set(5);
  Make_set(6);
  Make_set(7);
  Union(1, 2);
  std::cout << root(2) << '\n';
  Union(2, 3);
  Union(4, 5);
  Union(6, 7);
  Union(5, 6);
  Union(3, 7);
  return 0;
}
