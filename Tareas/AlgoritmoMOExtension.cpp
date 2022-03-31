#include<bits/stdc++.h>
#define ll long long
#define MAX 20000

struct Query{
    int L, R;
};

int valores[MAX];
int padres[MAX]; //Nos dice quien es el padre del nodo i
std::vector<int> hijos[MAX]; //Lista de los hijos de cada nodo
bool visitados[MAX]; //Lo usamos para hacer la DFS
std::vector<int> arbolDFS; //Tiene el arbol linealizado
std::vector<int> eulerTour;
int alturas[MAX]; //Guarda las alturas de cada nodo
int prim_visita[MAX]; //Marca la 1a visita en el euler Tour
int first[MAX]; //Dice la 1er visita en el DFS
int last[MAX];
int cantidades[5005] = {0}; //Nos guarda cuantas veces aparece cada numero
bool process[MAX]; //Nos almacena si ya esta o no metido el nodo
int orden[MAX]; //Tendra el orden de los nodos en el arbol linealizado
int block;
int ST[4*MAX][int(log(4*MAX))];
Query Q2[MAX];
int LCAs[MAX];
int currRes;


void DFS(int v){
    visitados[v] = 1;
    prim_visita[v] = eulerTour.size();
    first[v] = arbolDFS.size();
    arbolDFS.push_back(v);
    eulerTour.push_back(v);

    for(int i = 0; i < hijos[v].size(); i++){
      alturas[hijos[v][i]] = alturas[v] + 1;
      if(!visitados[hijos[v][i]])
        DFS(hijos[v][i]);
      if(i < hijos[v].size() - 1){
        eulerTour.push_back(v);
      }
    }
    arbolDFS.push_back(v);
    eulerTour.push_back(v);
    last[v] = arbolDFS.size() - 1;
}

void construye_STable(int n){
  //Inicializamos los intervalos de distancia 1
  for (int i = 0; i < n; i++)
      ST[i][0] = eulerTour[i];

  //Creamos el resto de la tabla
  for (int j = 1; (1 << j) <= n; j++) {
      for (int i = 0; (i + (1 << j) - 1) < n; i++) {
          if (alturas[ST[i][j - 1]] < alturas[ST[i + (1 << (j - 1))][j - 1]])
                  ST[i][j] = ST[i][j - 1];
          else
                  ST[i][j] = ST[i + (1 << (j - 1))][j - 1];
          }
      }
}

int LCA(int a, int b){
  //Vemos en donde esta guardado en el Euler tour cada nodo
  int L = prim_visita[a];
  int R = prim_visita[b];
  if(L > R){
    R = L;
    L = prim_visita[b];
  }

  int j = (int)log2(R - L + 1);

  if (ST[L][j] <= ST[R - (1 << j) + 1][j])
        return ST[L][j];

  else
        return ST[R - (1 << j) + 1][j];
}

void agrega(int n){
  int aux = 0;
  if(cantidades[valores[n]] >= 3)
    aux = 1;

  if(process[n]){
    process[n] = 0;
    cantidades[valores[n]]--;
    if(cantidades[valores[n]] < 3 && aux == 1){ //Si ahora cambio el dato
      currRes--;
      //std::cout << "cambio -"<< valores[n] << '\n';
    }
  }else{
    process[n] = 1;
    cantidades[valores[n]]++;
    if(cantidades[valores[n]] >= 3 && aux == 0){
      currRes++;
      //std::cout << "cambio +"<< valores[n]  << '\n';
    }
  }
}


bool ordena_visita(int a, int b){
  return prim_visita[a] < prim_visita[b];
}

bool ordena_q(Query x, Query y){
    //Ordena por bloques primero
    if (floor(x.L/block) != floor(y.L/block))
        return x.L/block < y.L/block;

    //Si estan en el mismo bloque ordena por el valor de R
    return x.R < y.R;
}

void queryResults(int N, int Q){

    //std::cout << typeid(Q2[0].L).name() << '\n';
    // Inicializamos L, R y la respuesta actual
    int currL = Q2[0].L, currR = Q2[0].R;
    int maxi = 0; int mini = 6000;
    for (int i = currL; i < currR + 1; i++)
      agrega(arbolDFS[i]);

    int LCa = LCA(arbolDFS[Q2[0].L], arbolDFS[Q2[0].R]);
    if(LCa != Q2[0].L && LCa != Q2[0].L)
        agrega(LCa);

    std::cout << "Query ("<<Q2[0].L<<", "<<Q2[0].R<<") = "<< currRes << '\n';

    if(LCa != Q2[0].L && LCa != Q2[0].L)
        agrega(LCa);

    // Recorremos las queries
    for (int i = 1; i < Q; i++){

        // Quitamos lo que no es necesario en la query
        while (currL < Q2[i].L){
            //std::cout << "c1 agrega nodo "<< currL+1 << '\n';
            agrega(arbolDFS[currL+1]);
            currL++;
        }

        // Agregamos los elementos de la izquierda
        while (currL > Q2[i].L){
            //std::cout << "c2 agrega nodo "<< currL-1 << '\n';
            agrega(arbolDFS[currL-1]);
            currL--;
        }

        while (currR < Q2[i].R){
            //std::cout << "c3 agrega nodo "<< currR+1 << '\n';
            agrega(arbolDFS[currR+1]);
            currR++;
        }

        while (currR > Q2[i].R){
            //std::cout << "c4 agrega nodo "<< currR-1 << '\n';
            agrega(arbolDFS[currR-1]);
            currR--;
        }

        LCa = LCA(arbolDFS[Q2[i].L], arbolDFS[Q2[i].R]);
        if(LCa != Q2[i].L && LCa != Q2[i].L)
            agrega(LCa);

        std::cout << "Query ("<<Q2[i].L<<", "<<Q2[i].R<<") = "<< currRes << '\n';

        if(LCa != Q2[i].L && LCa != Q2[i].L)
            agrega(LCa);

    }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N, Q, l, r;
  std::cin >> N;

  for (int i = 0; i < N; i++){
    std::cin >> valores[i];
    orden[i] = i;
  }

  padres[0] = 0;
  alturas[0] = 0;

  for (int i = 1; i < N; i++){
    std::cin >> padres[i];
		hijos[padres[i]].push_back(i);
  }

  DFS(0);
  block = floor(sqrt(arbolDFS.size()));
  //Ordena que nodos estan primero en el arreglo linealizado

  std::cin >> Q;
  Query Queries[Q];
  int lq, rq;
  for (int i = 0; i < Q; i++){
    std::cin >> lq >> rq;
    Queries[i].L = lq;
    Queries[i].R = rq;
  }

  //Ordena las queries
  //Primero es necesario ver si son del caso donde uno de los dos es el LCA o no


  int n = eulerTour.size();
  int log_n = log(n);
  construye_STable(n);

  for (int i = 0; i < Q; i++){
    LCAs[i] = LCA(Queries[i].L, Queries[i].R);
    std::cout << "LCA("<<Queries[i].L<<", "<<Queries[i].R<<") "<<LCAs[i] << '\n';
    if(LCAs[i] == Queries[i].L){
          std::cout << "lca "<< Queries[i].L<<", "<<Queries[i].R << '\n';
            Q2[i].L = first[Queries[i].L];
            Q2[i].R = first[Queries[i].R];
    }else{
          if(LCAs[i] == Queries[i].R){
            std::cout << "lca "<< Queries[i].L<<", "<<Queries[i].R << '\n';
            Q2[i].L = first[Queries[i].R];
            Q2[i].R = first[Queries[i].L];
          }else{
            if(last[Queries[i].L] < first[Queries[i].R]){
              Q2[i].L = last[Queries[i].L];
              Q2[i].R = first[Queries[i].R];
            }else{
              Q2[i].L = last[Queries[i].R];
              Q2[i].R = first[Queries[i].L];
            }
          }
    }
  }

  std::cout << "Previo al orde" << '\n';

  for (int i = 0; i < Q; i++) {
    std::cout << "("<<Q2[i].L<<", "<<Q2[i].R<<") " << '\n';
  }

  std::sort(Q2, Q2 + Q, ordena_q);

  for (size_t i = 0; i < 2*N; i++) {
    std::cout << arbolDFS[i] << " ";
  }
  std::cout  << '\n';

  queryResults(N, Q);

  /*std::cout << "despues del orden" << '\n';
  for (int i = 0; i < Q; i++) {
    std::cout << "("<<Q2[i].L<<", "<<Q2[i].R<<") " << '\n';
  }*/


  return 0;
  }
