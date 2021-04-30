#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

struct Node{
  int data;
  int rank;
  Node* parent;
};

map<int, Node*> mapa; //Con esto guardamos el nodo asociado a cada dato

void print_map(std::map<int, Node> const &m){
  for (auto it = m.cbegin(); it != m.cend(); ++it) {
        std::cout << "{" << (*it).first << "}\n";
    }
}

void Make_set(int a){
  Node* nodo = new Node();
  nodo->data = a;
  nodo->rank = 0;
  nodo->parent = nodo;
  mapa.insert (std::pair<int,Node*>(a, nodo));
}

int root(int a){
  Node* nodo;
  nodo = mapa[a];
  while((nodo->parent)->parent!=nodo->parent){
    nodo->parent=nodo->parent->parent;
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
  raiz_a = mapa[r_a];
  raiz_b = mapa[r_b];

  if(raiz_a->rank > raiz_b->rank){
    Node* aux= raiz_a;
    raiz_a=raiz_b;
    raiz_b=aux;
  }
    raiz_a->parent = raiz_b;
    raiz_b->rank++;
}
}


int main(){
int n, m, k, aux1, aux2, root0,res;
int e=0;
while (cin) {
  if(e!=0)
    std::cout  << '\n';
  e=1;
  std::cin >> n>> m;
  res=0;
  Make_set(0);
  for (int i = 0; i < m; i++) {
    std::cin >> k;
    for (int j = 0; j < k; j++) {
      std::cin >> aux1;
      Make_set(aux1);
      if(j!=0){ //Guardamos el primero y le decimos a los demas que sus conjuntos se junten
        Union(aux1, aux2);
      }else{
        aux2=aux1;
      }
    }
  }
  root0=root(0);
  for (auto it = mapa.cbegin(); it != mapa.cend(); ++it) {
        if(root((*it).second->data)==root0)
          res++;
    }
  std::cout << res;
  mapa.clear();

}
  return 0;
}
