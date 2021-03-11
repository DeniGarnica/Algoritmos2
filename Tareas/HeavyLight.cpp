#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int padresLCA[100000][100];
//funciones del st
int operacion(int a, int b){
  return a+b;
}
void construir(vector<int> &tree, int* positions, int*A, vector<int> chain, int vertex, int L, int R){ //A son nuestros valores iniciales
  if(L==R){ //Si son iguales, nos referimos a una hoja
    tree[vertex]=A[chain[L]];
    //std::cout << "hoja: "<< tree[vertex] << '\n';
    positions[chain[L]]=vertex; //de esta manera guardo en que posicion del tree quedaro cada hoja
    //std::cout << "El nodo "<< chain[L]<< " quedo en "<< vertex << '\n';
  }else{
    int  nL = 2*vertex+1;
    int  nR = 2*vertex+2;
    construir(tree, positions, A, chain, nL, L, (L+R)/2); //construye el arbol izquierdo
    construir(tree, positions, A, chain,  nR, (L+R)/2 +1, R); //construye el arbol derecho
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
void actualizaHoja (vector<int> &tree, int vertex, int k){
  tree[vertex]= k;
  int padre = (vertex-1)/2;
  tree[padre]= operacion(tree[2*padre+1], tree[2*padre+2]);

  do{
    padre=(padre-1)/2;
    tree[padre]= operacion(tree[2*padre+1], tree[2*padre+2]);
  }while(padre != 0);
}

int subsize(int i, vector<vector<int>> hijos, int *subarbolsize, int *level){ // con esta funcion recursiva le asigna los pesos de cada subarbol al arreglo subarbolsize
  if(hijos[i].empty()){
    subarbolsize[i]=1;
    level[i]=0;
    //std::cout <<  "level de "<< i<< " = "<<level[i] << '\n';
    //std::cout << "Tam del arbol"<< i<<": " << subarbolsize[i]<< '\n';
    return 1;
  }else{
    int aux=0;
    for (size_t j = 0; j < hijos[i].size(); j++) {
      aux = aux+ subsize(hijos[i][j], hijos, subarbolsize, level);
    }
    //std::cout <<  "level de "<< i<< " = "<<level[hijos[i][0]]+1 << '\n';
    level[i]=level[hijos[i][0]]+1;
    subarbolsize[i] = aux+1;
    //std::cout << "Tam del arbol"<< i<<": " << subarbolsize[i]<< '\n';
    return subarbolsize[i];
  }
}
void chains(int i, int *subarbolsize, vector<vector<int>> hijos, vector<vector<int>> &chain, int* posChain ,int* curr_chain, int* numChain){
  chain[curr_chain[0]].push_back(i);//se mete el nodo a la cadena actual
  posChain[i]=chain[curr_chain[0]].size()-1;
  numChain[i]=curr_chain[0];//guardamos en que cadena esta
  //std::cout << "mete nodo "<< i<< " a la cadena "<< curr_chain[0] << '\n';
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
    chains(nodoPesado, subarbolsize, hijos, chain, posChain, curr_chain, numChain); //metemos el hijo mas pesado a la misma cadena

    for (size_t j = 0; j < hijos[i].size(); j++) {
      if(hijos[i][j]!=nodoPesado){
        curr_chain[0]++; //cambiamos el numero de cadena
        chains(hijos[i][j], subarbolsize, hijos, chain, posChain, curr_chain, numChain);//ponemos el resto de los hijos a otras cadenas
      }
    }
  }else{
    return;
  }
}

int lca(int u, int v, int* level){
    if (level[v] < level[u])
        swap(u, v);
    int dif = level[v] - level[u];

    for (int i=0; i<level[0]; i++){
        if ((dif>>i)&1)
            v = padresLCA[v][i]; //*(*(padresLCA+v)+i)
        }
    if (u == v)// ahora estan en el mismo nivel
        return u;

    for (int i=level[0]-1; 0<=i; i--)
        if (padresLCA[u][i] != padresLCA[v][i]){
            u = padresLCA[u][i];
            v = padresLCA[v][i];
        }
    return padresLCA[u][0];
}

int subir( int* numChain, vector<vector<int>> st, int* posChain, int*padre, int lcap, int n1, vector<vector<int>> &chain){
  int cadenaActual = numChain[n1];
  std::cout << "cadena actual "<<cadenaActual << '\n';
  std::cout << "cadena del lca " <<numChain[lcap] <<'\n';
  int nodoActual=n1;
  std::cout << "nodo actual "<<nodoActual << '\n';
  int ans1=0;
  int aux,p;
  while(cadenaActual!=numChain[lcap]){
    ans1 += rango(st[cadenaActual], 0, 0, chain[cadenaActual].size()-1, 0, posChain[nodoActual]);
    p = chain[numChain[n1]][0];
    cadenaActual=numChain[padre[p]];

    nodoActual=padre[p];
    std::cout << "cadena actual "<<cadenaActual << '\n';
    std::cout << "cadena del lca " <<numChain[lcap] <<'\n';
    std::cout << "nodo actual "<<nodoActual << '\n';
    std::cout << "ans "<<ans1 << '\n';
  }
  std::cout << "pos lcap "<< posChain[lcap] << '\n';
  std::cout << "pos n "<< posChain[nodoActual] << '\n';
  for (size_t i = 0; i < chain[numChain[nodoActual]].size(); i++) {
    std::cout << "cadena actual "<<chain[numChain[nodoActual]][i] << '\n';
  }
  std::cout << "chain[numChain[lcap]].size()-1 "<< chain[numChain[nodoActual]].size()<< '\n';
  ans1 += rango(st[numChain[lcap]], 0, 0, chain[numChain[lcap]].size()-1, posChain[lcap], posChain[nodoActual]);
  std::cout << "ans "<< ans1 << '\n';
  return ans1;
}

int main(){
  int n, q, cambio, valornuevo, n1, n2;
  char peticion;
  std::cin >> n >> q;
  int A[n]; int padre[n]; int numChain[n]; int subarbolsize[n]; int positions[n]; int level[n]; int posChain[n];
  vector<vector<int>> hijos; vector<vector<int>> st; vector<vector<int>> chain;

  padre[0]=0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> A[i];
    hijos.push_back({});
    st.push_back({});
    chain.push_back({});
  }
  memset(padresLCA,-1, sizeof(padresLCA));
  padresLCA[0][0]=0;
  for (size_t i = 0; i < n-1; i++) {
    std::cin >> padre[i+1];
    hijos[padre[i+1]].push_back(i+1); //aqui almacenamos los hijos de cada nodo
    padresLCA[i+1][0]=padre[i+1];
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
  subsize(0, hijos, subarbolsize, level); //asigna los tama;os de cada subarbol en el arreglo subarbolsize
  int curr_chain[1]; curr_chain[0]=0;//hice este arreglo de tam 1 para poder ir modificando cual es la cadena actual apesar de ser llamadas recursivas
  chains(0, subarbolsize, hijos, chain, posChain, curr_chain, numChain);//Creamos las cadenas
  int a = 0;
  while(!chain[a].empty()&&a<n){ // creamos los st de las cadenas
    vector<int> s (2*chain[a].size()-1, 0);
    construir(s, positions, A, chain[a], 0, 0, chain[a].size()-1);
    st[a]=s;
    a++;
  }
  int max_level= level[0]; //donde si el level[i]=0, es una hoja, asi que level[0] es el valor mas alto de level
    //tabla de lca, como a lo mas puede tener level[0] ancestros, entonces 1<level_max
  for (int i=1; i<max_level; i++){
          for (int node = 1; node <= n; node++){
              if (padresLCA[node][i-1] != -1)
                  padresLCA[node][i] =   padresLCA[padresLCA[node][i-1]][i-1];
          }
      }
      //Empezamos las preguntas
  for (size_t k = 0; k < q; k++) {
    std::cin >> peticion;
    if(peticion=='U'){
      std::cin >> cambio >> valornuevo;
      actualizaHoja (st[numChain[cambio]], positions[cambio], valornuevo);
      A[cambio]=valornuevo;
    }
    if(peticion=='P'){
      std::cin >> n1 >> n2;
      int lcap = lca(n1, n2, level);
      std::cout << "lca " << lcap<< '\n';
      int ans1= subir(numChain,st, posChain, padre, lcap, n1, chain);
      int ans2= subir(numChain,st, posChain, padre, lcap, n2, chain);
      int ans= ans1+ans2-A[lcap];
      std::cout << ans << '\n';
    }
  }

  return 0;
}
