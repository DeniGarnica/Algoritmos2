#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct _Node{
  long long x, cnt, maxi;
  long long p;
  _Node *l, *r;
  _Node (long long v): x(v), p(((long long)(rand())<<32)^rand()), cnt(1), l(NULL), r(NULL), maxi(v) {}
  ~_Node() {delete l; delete r;}
  void recalc(){
    cnt = 1;
    cnt += ((l)?(l->cnt):0);
    cnt += ((r)?(r->cnt):0);

    if(l!=NULL && r!=NULL){//Si tiene ambos hijos
      maxi = max(max(l->maxi, r->maxi), maxi);
    }else{
      if(l!=NULL){ //Si solo tiene el hijo izq
        maxi=max(l->maxi, maxi);
      }
      if(r!=NULL){ //Si solo tiene el hijo der
        maxi = max(r->maxi, maxi);
      }
      if(l==NULL && r==NULL){
        maxi = x;
      }
    }
  }
}; typedef _Node *Node;

void printArbol(Node a, int con){
  if(a==NULL){
    return;
  }else{
    printArbol(a->r, con+1);
    for(int i=0; i<con;i++){
      std::cout << " ";
    }
    //std::cout << a->x << '\n';
    std::cout << a->x <<", "<<a->maxi<<'\n';
    //std::cout << a->x <<", "<<a->cnt<< ", p: "<<a->p<<'\n';
    printArbol(a->l, con+1);
  }
}

Node merge(Node l, Node r){ //Se asume que los arboles que nos pasan estan bien acomodados
  if(!l || !r) return l? l:r;
  if(l->p > r->p){
    l->r = merge(l->r, r);
    l->recalc();
    return l;
  }else{
    r->l = merge(l, r->l);
    r->recalc();
    return r;
  }
}

void SplitByValue(Node n, long long d, Node &l, Node &r){ //En l quedan los menores a d, en r quedan los mayores iguales a d.
  if(!n) return; //Si N esta vacio
  l=r=NULL;
  if(n->x <d){
    SplitByValue(n->r, d, n->r, r);
      l=n;
  }else{
    SplitByValue(n->l, d, l, n->l);
    r=n;
  }
  n->recalc();
}

void SplitByPosition(Node n, long long pos, Node &l, Node &r, long long ad)//Se empeiza contando del 1, pues queremos separar los primeros pos nodos
{
  //l=r=NULL;
  if(!n) return void( l = r = NULL); //Si N esta vacio
  long long cur_key = ad;
  long long hi = 0;
  if(n->l!=NULL){
    hi=n->l->cnt;
    cur_key += hi;
  }
  if(pos <= cur_key){
    SplitByPosition(n->l, pos, l, n->l, ad);
    r=n;
  }else{
    SplitByPosition(n->r, pos, n->r, r, ad + 1 + hi);
    l=n;
  }
  n->recalc();
}

long long getValueInPos(Node n, long long pos){ //Se empieza contando del 1
  Node l = NULL;
  Node r = NULL;
  SplitByPosition(n, pos, l, r, 0);
  long long value = l->x;
  merge(l,r);
  return value;
}

void insertInPosition(Node arbol, Node n, long long pos){
  Node l1 = NULL;
  Node l2 = NULL;
  if(pos>1){
    SplitByPosition(arbol, pos, l1, arbol, 0);
    SplitByPosition(l1, pos-1, l1, l2, 0);
    merge(l1, n);
    if(n->cnt>l1->cnt){
      merge(n, l2);
      if(n->cnt>l2->cnt){
        merge(n, arbol);
      }else{
        merge(l2,arbol);
      }
    }else{
      merge(l1,l2);
      if(l1->cnt>l2->cnt){
        merge(l1, arbol);
      }else{
        merge(l2,arbol);
      }
    }
  }else{
    SplitByPosition(arbol, pos, l1, arbol, 0);
    merge(n,l1);
    if(n->cnt>l1->cnt){
      merge(n, arbol);
    }else{
      merge(l1,arbol);
    }
  }
}

void eraseInPosition(Node arbol, long long pos){
  Node l1 = NULL;
  Node l2 = NULL;
  SplitByPosition(arbol, pos, l1, arbol, 0);
  SplitByPosition(l1, pos-1, l1, l2, 0);
  merge(l1, arbol);
  delete l2;
}

int main(){
  Node root = NULL;
  int numPelotas=0;
  std::cin >> numPelotas;
  for (int i = 0; i < numPelotas; i++) {
    long long var;
    std::cin >> var;
    Node n0 = new _Node(var);
    root = merge(root, n0);
  }
  printArbol(root,0);
  int numPeticiones=0;
  int peticion;
  long long P1;
  long long P2;
  std::cin >> numPeticiones;
  for (int i = 0; i < numPeticiones; i++) {
    std::cin >> peticion;

    if(peticion==0){
      std::cin >> P1 >> P2;
    }
    if(peticion==1){
      std::cin >> P1;
    }
    if(peticion==2){
      std::cin >> P1 >> P2;
    }
    if(peticion==3){
      std::cin >> P1;
    }

  }

  return 0;
}
