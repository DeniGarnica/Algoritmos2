#include<bits/stdc++.h>
#define ll long long
#define MAX 20000

int valores[MAX];
int padres[MAX]; //Nos dice quien es el padre del nodo i
std::vector<ll> hijos[MAX]; //Lista de los hijos de cada nodo
bool visitados[MAX]; //Lo usamos para hacer la DFS
std::vector<ll> arbolDFS; //Tiene el arbol linealizado
std::vector<ll> eulerTour;
int alturas[MAX]; //Guarda las alturas de cada nodo
int prim_visita[MAX]; //Marc a la 1a visita en el euler Tour
int cantidades[5005]; //Nos guarda cuantas veces aparece cada numero
bool process[MAX]; //Nos almacena si ya esta o no metido el nodo


void DFS(int v){
    visitados[v] = 1;
    prim_visita[v] = eulerTour.size();
    arbolDFS.push_back(v);
    eulerTour.push_back(v);
    std::cout << v << " ";

    for(int i = 0; i < hijos[v].size(); i++){
      alturas[hijos[v][i]] = alturas[v] + 1;
      if(!visitados[hijos[v][i]])
        DFS(hijos[v][i]);
      if(i < hijos[v].size() - 1){
        eulerTour.push_back(v);
        std::cout << v << " ";
      }
    }
    arbolDFS.push_back(v);
    eulerTour.push_back(v);
    std::cout << v << " ";
}

void agrega(int n){
  if(process[n]){
    process[n] = 0;
    cantidades[valores[n]]--;
  }else{
    process[n] = 1;
    cantidades[valores[n]]++;
  }
}

int cuenta(int l, int r){
  res = 0;
  for (int i = l; i < r; i++) 
    if(cantidades[i] >= 3)
      res++;
  return res
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N, Q, l, r;
  std::cin >> N;

  for (int i = 0; i < N; i++)
    std::cin >> valores[i];

  padres[0] = 0;
  alturas[0] = 0;

  for (int i = 1; i < N; i++){
    std::cin >> padres[i];
		hijos[padres[i]].push_back(i);
  }

  DFS(0);

  std::cout  << '\n';
  for (int i = 0; i < N; i++) {
    std::cout << prim_visita[i] << " ";
  }

  int raiz = floor(sqrt(N));

  //std::cin >> Q;
  //for (int i = 0; i < Q; i++)
  //  std::cin >> l >> r;
    return 0;
  }
