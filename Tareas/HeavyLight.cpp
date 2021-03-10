#include <iostream>
#include <vector>
using namespace std;

//funciones del st
int operacion(int a, int b){
  return a+b;
}
void construir(vector<int> &tree, vector<int> A, int vertex, int L, int R){ //A son nuestros valores iniciales
  if(L==R){ //Si son iguales, nos referimos a una hoja
    tree[vertex]=A[R];
    //std::cout << "hoja: "<< tree[vertex] << '\n';
    //A[L]=vertex; //de esta manera guardo en que posicion del tree quedaro cada hoja
  }else{
    int  nL = 2*vertex+1;
    int  nR = 2*vertex+2;
    construir(tree, A, nL, L, (L+R)/2); //construye el arbol izquierdo
    construir(tree, A, nR, (L+R)/2 +1, R); //construye el arbol derecho
    tree[vertex] = operacion(tree[nL], tree[nR]); //asigna al nodo la operacion correspondiente de sus dos hijos
    //std::cout << "nodo: "<< tree[vertex] << '\n';
  }
}
int rango(vector<int> &tree, int vertex, int L, int R, int l, int r){ //[l,r] es el rango que se esta buscando
    if(l>R|| r < L) return -1; //si esta fuera del rango
    if(L>= l && R <= r) return tree[vertex]; //si esta completamente contenido

    //Si solo esta parcialmente contenido busca en los hijos
    int p1 = rango(tree, 2*vertex +1, L, (L+R)/2, l, r);
    int p2 = rango(tree, 2*vertex + 2, (L+R)/2 + 1, R, l, r);
    if (p1== -1) return p2;
    if (p2== -1) return p1;
    return operacion(p1, p2);
}
void actualizaHoja (vector<int> &tree, vector<int> A, int vertex, int k){
  tree[A[vertex]]= k;
  int padre = (A[vertex]-1)/2;
  tree[padre]= operacion(tree[2*padre+1], tree[2*padre+2]);

  do{
    padre=(padre-1)/2;
    tree[padre]= operacion(tree[2*padre+1], tree[2*padre+2]);
  }while(padre != 0);
}

int subsize(int i, vector<vector<int>> hijos, int *subarbolsize){ // con esta funcion recursiva le asigna los pesos de cada subarbol al arreglo subarbolsize
  if(hijos[i].empty()){
    subarbolsize[i]=1;
    //std::cout << "Tam del arbol"<< i<<": " << subarbolsize[i]<< '\n';
    return 1;
  }else{
    int aux=0;
    for (size_t j = 0; j < hijos[i].size(); j++) {
      aux = aux+ subsize(hijos[i][j], hijos, subarbolsize);
    }
    subarbolsize[i] = aux+1;
    //std::cout << "Tam del arbol"<< i<<": " << subarbolsize[i]<< '\n';
    return subarbolsize[i];
  }
}
void chains(int i, int *subarbolsize, vector<vector<int>> hijos, vector<vector<int>> &chain, int* curr_chain){

  chain[curr_chain[0]].push_back(i);//se mete el nodo a la cadena actual
  //std::cout << "se agrego "<< i <<" a la cadena"<< curr_chain[0] << '\n';
  //Buscamos el hijo mas pesado
  if(!hijos[i].empty()){
    int max=0;
    int nodoPesado=0;
    for (size_t j = 0; j < hijos[i].size(); j++) {
      if(max<subarbolsize[hijos[i][j]]){
        max=subarbolsize[hijos[i][j]];
        nodoPesado=hijos[i][j];
      }
    }
    chains(nodoPesado, subarbolsize, hijos,chain, curr_chain); //metemos el hijo mas pesado a la misma cadena

    for (size_t j = 0; j < hijos[i].size(); j++) {
      if(hijos[i][j]!=nodoPesado){
        curr_chain[0]++; //cambiamos el numero de cadena
        chains(hijos[i][j], subarbolsize, hijos, chain, curr_chain);//ponemos el resto de los hijos a otras cadenas
      }
    }
  }else{
    return;
  }
}



int main(){
  int n, q;
  std::cin >> n >> q;
  int A[n];
  int padre[n];
  vector<vector<int>> hijos;
  int subarbolsize[n];
  padre[0]=0;
  vector<vector<int>> st;
  vector<vector<int>> chain;
  for (size_t i = 0; i < n; i++) {
    std::cin >> A[i];
    hijos.push_back({});
    st.push_back({});
    chain.push_back({});
  }
  for (size_t i = 0; i < n-1; i++) {
    std::cin >> padre[i+1];
    hijos[padre[i+1]].push_back(i+1); //aqui almacenamos los hijos de cada nodo
  }
  /*for (size_t i = 0; i < n-1; i++) { //imprime los hijos
    std::cout << i<<": ";
    if(!hijos[i].empty()){
      for (size_t j = 0; j < hijos[i].size(); j++) {
        std::cout << hijos[i][j]<<" ";
      }
    }
    std::cout  << '\n';
  }*/

  subsize(0, hijos, subarbolsize); //asigna los tama;os de cada subarbol en el arreglo subarbolsize

  int curr_chain[1]; //hice este arreglo de tam 1 para poder ir modificando cual es la cadena actual apesar de ser llamadas recursivas
  curr_chain[0]=0;
  chains(0, subarbolsize, hijos, chain, curr_chain);//Creamos las cadenas
  int a = 0;
  while(!chain[a].empty()&&a<n){ // creamos los st de las cadenas
    vector<int> s (2*chain[a].size()-1, 0);
    construir(s, chain[a], 0, 0, chain[a].size()-1);
    st[a]=s;
    a++;
  }
    //vector<int> s (2*chain[0].size()-1, 0);
    //construir(s, chain[0], 0, 0, chain[0].size()-1);
  for (size_t i = 0; i < 2*chain[3].size()-1; i++) {
    std::cout <<  st[3][i] <<" ";
  }


  return 0;
}
