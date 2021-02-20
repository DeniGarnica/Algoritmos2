#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int operacion(int a, int b){
  if(a<b){
    return b;
  }else{
    return a;
  }
}

void construir(int *tree, int *A, int vertex, int L, int R){ //A son nuestros valores iniciales
  if(L==R){ //Si son iguales, nos referimos a una hoja
    tree[vertex]=A[L];
  }else{
    int  nL = 2*vertex+1;
    int  nR = 2*vertex+2;
    construir(tree, A, nL, L, (L+R)/2); //construye el arbol izquierdo
    construir(tree, A, nR, (L+R)/2 +1, R); //construye el arbol derecho
    tree[vertex] = operacion(tree[nL], tree[nR]); //asigna al nodo la operacion correspondiente de sus dos hijos
  }
}

int rango(int* tree, int vertex, int L, int R, int l, int r){ //[l,r] es el rango que se esta buscando
    if(l>R|| r < L) return -1; //si esta fuera del rango
    if(L>= l|| R <= r) return tree[vertex]; //si esta completamente contenido

    //Si solo esta parcialmente contenido busca en los hijos
    int p1 = rango(tree, 2*vertex +1, L, (L+R)/2, l, r);
    int p2 = rango(tree, 2*vertex + 2, (L+R)/2 + 1, R, l, r);
    if (p1== -1) return p2;
    if (p2== -1) return p1;
    return operacion(p1, p2);
}

/*int query(int l, int r){
  return rango(0, 0, N, l, r);
}*/

void actualizaHoja (int* tree, int* A, int vertex, int k){
  A[vertex]= k;
  int padre = (vertex-1)/2;

  do{
    tree[padre]=operacion(tree[2*padre+1], tree[2*padre+2]);
    padre=(padre-1)/2;
  }while(padre != 0);
}

int main(){
  int n, aux, l, r;
  std::cin >> n;
  int A[n];
  for (int i=0; i<n; i++) {
    std::cin >> A[i];
  }
  int B[2*n];
  construir(B, A, 0, 0, n-1);
  std::cout << "rango a buscar" << '\n';
  std::cin >> l >> r;
  std::cout << rango(B, 0, 0, n, l, r)<< '\n';

  return 0;
}
