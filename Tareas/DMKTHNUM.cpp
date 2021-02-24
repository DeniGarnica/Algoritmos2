#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int* operacion(int n, int* a, int* b){
  int *B;
  B = new int[n];
  for(int i=0;i<n;i++){
    B[i]=a[i]+b[i];
  }
  return B;
}

int bs(int* A, int l, int r, int k){
  if (r >= l) {
      int mid = l + (r - l) / 2;
      if (A[mid] == k)
          return mid;
      if (A[mid] > k){
        if(A[mid-1]<k)
          return mid;
        return bs(A, l, mid - 1, k);
      }
      return bs(A, mid + 1, r, k);
    }
    return -1;
}

int resultado(int n, int* A, int k){
  int res = bs(A, 0, n, k);
  if(A[res-1]==0)
    return res;
  while(A[res]==A[res-1]){
    res--;
  }
  return res;
}


void construir(int n, int **tree, int *A, int vertex, int L, int R){ //A son nuestros valores iniciales
  if(L==R){ //Si son iguales, nos referimos a una hoja
    int* H;
    H = new int[n];
    for(int i=0;i<n;i++){
      if(A[L]<=i){
        H[i]=1;
      }else{
        H[i]=0;
      }
    }
    tree[vertex]= H;
    A[L]=vertex; //de esta manera guardo en que posicion del tree quedaron cada hoja
  }else{
    int  nL = 2*vertex+1;
    int  nR = 2*vertex+2;
    construir(n, tree, A, nL, L, (L+R)/2); //construye el arbol izquierdo
    construir(n, tree, A, nR, (L+R)/2 +1, R); //construye el arbol derecho
    tree[vertex] = operacion(n, tree[nL], tree[nR]); //asigna al nodo la operacion correspondiente de sus dos hijos
  }
}

int* rango(int n, int** tree, int vertex, int L, int R, int l, int r){ //[l,r] es el rango que se esta buscando
    if(l>R|| r < L) return NULL; //si esta fuera del rango
    if(L>= l && R <= r) return tree[vertex]; //si esta completamente contenido

    //Si solo esta parcialmente contenido busca en los hijos
    int* p1 = rango(n, tree, 2*vertex +1, L, (L+R)/2, l, r);
    int* p2 = rango(n, tree, 2*vertex + 2, (L+R)/2 + 1, R, l, r);
    if (p1== NULL) return p2;
    if (p2== NULL) return p1;
    return operacion(n, p1, p2);
}


void actualizaHoja (int n, int** tree, int* A, int vertex, int k){
  int *B;
  B = new int[n];
  for(int i=0;i<n;i++){
    if(k<=i){
      B[i]=1;
    }else{
      B[i]=0;
    }
  }
  tree[A[vertex]]= B;

  int padre = (A[vertex]-1)/2;
  tree[padre]= operacion(n, tree[2*padre+1], tree[2*padre+2]);

  do{
    padre=(padre-1)/2;
    tree[padre]= operacion(n, tree[2*padre+1], tree[2*padre+2]);
  }while(padre != 0);
}

int main(){
  int n, aux, l, r;
  std::cin >> n;
  int A[n];
  int Q[n];
  int m=0;
  for (int i=0; i<n; i++) {
    std::cin >> A[i];
    Q[i]=A[i];
    if(m<A[i]){
      m=A[i];
    }
  }
  m++;
  int* tree[2*n];
  int* rango1;
  construir(m, tree, A, 0, 0, n-1);
  int p, peticion, k, idx;
  std::cin >> p;
  for (int i=0; i<p; i++) {
    std::cin >> peticion;
    if(peticion==0){
      std::cin >> l;
      std::cin >> r;
      std::cin >> k;
      if(k<=r-l){
        rango1 = rango(m, tree, 0, 0, n-1, l, r);
        std::cout << resultado(m, rango1, k+1) << '\n';
      }
    }else{
      std::cin >> idx;
      std::cin >> k;
      if(k<=m)
        actualizaHoja (m, tree, A, idx, k);
    }
  }


  return 0;
}
