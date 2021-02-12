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
  SplitByPosition(arbol, pos, l1, arbol, 0);
  std::cout << "arbol actual" << '\n';
  printArbol(arbol, 0);
  SplitByPosition(l1, pos-1, l1, l2, 0);
  merge(l1, n);
  std::cout << "arbol actual n" << '\n';
  printArbol(n, 0);
  merge(n, l2);
  std::cout << "arbol actual l2" << '\n';
  printArbol(l2, 0);
  merge(l2, arbol);
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
  /*SplitByPosition(root, 2, l, r, 0);
  std::cout << "arbol izq" << '\n';
  printArbol(l,0);
  std::cout << "arbol der" << '\n';
  printArbol(r,0);*/
  //long long v = getValueInPos(root, 3);
  //std::cout << "SplitByPosition: " <<  v << '\n';
  Node n7 = new _Node(15);
  eraseInPosition(root, 2);
  std::cout << "nuevo arbol " << '\n';
  printArbol(root,0);
  return 0;
}
