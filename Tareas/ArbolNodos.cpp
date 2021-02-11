#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct _Node{
  int x, cnt;
  long long p;
  _Node *l, *r;
  _Node (int v): x(v), p(((long long)(rand())<<32)^rand()), cnt(1), l(NULL), r(NULL) {}
  ~_Node() {delete l; delete r;}
  void recalc(){
    cnt = 1;
    cnt += ((l)?(l->cnt):0);
    cnt += ((r)?(r->cnt):0);

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
    std::cout << a->x << '\n';
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

void insertaArbol(Node &a, Node n){
  if(!a){
    a=n;
  }else{
    if(n->p > a->p){
      SplitByValue(a, n->x, n->l, n->r);
      a=n;
    }else{
      insertaArbol(n->x < a->x ? a->l : a->r, n);
    }
  }
}


int main(){
  Node root=NULL;
  Node n0= new _Node(15);
  Node n1= new _Node(14);
  root = merge(n0, n1);
  printArbol(root,0);

  return 0;
}
