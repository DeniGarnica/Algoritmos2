#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct _Node{
  long long x, cnt;
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
    //std::cout << a->x <<", "<<a->cnt<< '\n';
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


void SplitByPosition(Node n, long long pos, Node &l, Node &r, long long ad){
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

long long getValueInPos(Node n, long long pos){ //Empezando desde 0
  if(n->cnt-1==pos) return n->x;
  if(n->cnt-1 <pos){
    return getValueInPos(n->r, pos);
  }else{
    return getValueInPos(n->l, pos);
  }
}



int main(){
  Node root = NULL;
  Node n0 = new _Node(11);
  Node n1 = new _Node(21);
  Node n2 = new _Node(35);
  Node n3 = new _Node(43);
  Node n4 = new _Node(56);
  Node n5 = new _Node(67);
  Node n6 = new _Node(86);
  root = merge(n0, n1);
  root = merge(root, n2);
  root = merge(root, n3);
  root = merge(root, n4);
  root = merge(root, n5);
  root = merge(root, n6);
  printArbol(root,0);
  Node l = NULL;
  Node r = NULL;
  SplitByPosition(root, 2, l, r, 0);
  std::cout << "arbol izq" << '\n';
  printArbol(l,0);
  std::cout << "arbol der" << '\n';
  printArbol(r,0);
  return 0;
}
