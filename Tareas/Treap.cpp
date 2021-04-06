#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct _Node {
  long long x, p, cnt; //x:clave, p: prioridad, cnt: elementos en subarbol
  _Node *l, *r; //punteros subarbol
  _Node (long long v) : x(v), p(((long long)(rand()) << 32)^rand()), cnt(1), l(NULL), r(NULL) {}
  ~_Node () {delete l; delete r;}
  void recalc(){ //Aqui se actualizaria cualquier valor que se lleve en los nodos
    cnt = 1 ;
    cnt += ((l)?(l->cnt):0);
    cnt += ((r)?(l->cnt):0);
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
  Node root, n, m, o;
  long long l = 6;
  n = new _Node(6);
  m = new _Node(3);
  o = new _Node(15);
  insertaArbol(root, n);
  insertaArbol(root, m);
  insertaArbol(root, o);
  std::cout << n->x << '\n';
  printArbol(n, 0);

  return 0;
}
