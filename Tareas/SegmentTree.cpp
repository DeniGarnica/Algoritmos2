#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int operacion(int a, int b){
  if(a<b){
    return a;
  }else{
    return b;
  }
}

void construir(int *tree, int *A, int vertex, int L, int R){ //A son nuestros valores iniciales
  if(L==R){ //Si son iguales, nos referimos a una hoja
    tree[vertex]=A[L];
    A[L]=vertex; //de esta manera guardo en que posicion del tree quedaro cada hoja
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
    if(L>= l && R <= r) return tree[vertex]; //si esta completamente contenido

    //Si solo esta parcialmente contenido busca en los hijos
    int p1 = rango(tree, 2*vertex +1, L, (L+R)/2, l, r);
    int p2 = rango(tree, 2*vertex + 2, (L+R)/2 + 1, R, l, r);
    if (p1== -1) return p2;
    if (p2== -1) return p1;
    return operacion(p1, p2);
}


void actualizaHoja (int* tree, int* A, int vertex, int k){
  tree[A[vertex]]= k;
  int padre = (A[vertex]-1)/2;
  tree[padre]= operacion(tree[2*padre+1], tree[2*padre+2]);

  do{
    padre=(padre-1)/2;
    tree[padre]= operacion(tree[2*padre+1], tree[2*padre+2]);
  }while(padre != 0);
}

int main(){
  int n, aux, l, r;
  std::cin >> n;
  int A[n];
  for (int i=0; i<n; i++) {
    std::cin >> A[i];
  }
  int tree[2*n];
  construir(tree, A, 0, 0, n-1);
  std::cout << "rango a buscar" << '\n';
  std::cin >> l >> r;
  std::cout << rango(tree, 0, 0, n-1, l, r)<< '\n';

  actualizaHoja (tree, A, 2, 8);

  /*std::cout << "Hojas del actualizado: " << '\n';
  for (int i=0; i<n; i++) {
    std::cout << tree[A[i]] << " ";
  }*/

  std::cout <<'\n' <<"rango a buscar del actualizado" << '\n';
  std::cin >> l >> r;
  std::cout << rango(tree, 0, 0, n-1, l, r)<< '\n';

  return 0;
}
