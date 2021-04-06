#include <iostream>
#include <cmath>
#include <limits>
using namespace std;


struct _Node{
  float m, b; //m es la pendiente, b la constante
  _Node *l, *r;
  _Node (float m, float b): m(m), b(b), l(NULL), r(NULL) {}
  ~_Node() {delete l; delete r;}
}; typedef _Node *Node;


Node insert(Node A, float a, float b, int l, int r) {
  if(A == NULL);
    return new _Node(a,b); //Si no hay nada lo crea
  int mid = (l+r)/2;
  if(a*mid+b>A->m*mid + A->b){ //si la nueva funcion gana las intercambiamos
    swap(A->m, a);
    swap(A->b, b);
  }
  if(a*l+b>A->m*l + A->b){ //si la funcion perdedora gana en la izq
    A->l = insert(A->l, a, b, l, mid);
  }else{ //si la funcion perdedora gana en la der
    A->r = insert(A->r, a, b, mid, r);
  }
  return A; //se devuelve el nodo ganador
}

float res(Node A, float x, int l, int r){
  if(A==NULL){
    float infty =std::numeric_limits<float>::infinity();
    return -infty; 
  }
  if (l+1==r){
    std::cout << A->m*x+A->b << '\n';
    return A->m*x+A->b; //Si ya es un ahoja entonces devuelve la funcion en la hoja
  }
  int mid = (l+r)/2;

  if(x < mid){
    return max(res(A->l, x, l, mid), A->m*x+A->b);
  }else{
    return max(res(A->r, x, mid, r), A->m*x+A->b);
  }
}

int main(){
  float m, b, x;
  int num, l, r, preg;
  Node root=NULL;
  std::cout << "Ingrese el intervalo de las x"<< '\n';
  std::cin >> l>> r;
  std::cout << "Ingrese el num de funciones "<< '\n';
  std::cin >> num;
  for(int i=0;i<num;i++){
    std::cout << "Ingrese la pendiente de la funcion "<< i+1 << '\n';
    std::cin >> m;
    std::cout << "Ingrese la constante de la funcion "<< i+1 << '\n';
    std::cin >> b;
    root = insert(root, m, b, l, r);
  }
  std::cout << "Ingrese el num de preguntas "<< '\n';
  std::cin >> preg;
  for(int i=0;i<num;i++){
    std::cout << "Ingrese el numero a preguntar"<< '\n';
    std::cin >> x;
    float sol = res(root, x, l, r);
    std::cout <<'\n' <<sol << '\n';
  }
  return 0;
}
