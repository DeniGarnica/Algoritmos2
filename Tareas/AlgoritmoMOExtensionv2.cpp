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
int last[MAX];  //Dice la ultima visita en el DFS
int cantidades[5005] = {0}; //Nos guarda cuantas veces aparece cada numero
bool process[MAX]; //Nos almacena si ya esta o no metido el nodo
int block; //Tamanio de las clases
int ST[4*MAX][int(log(4*MAX))]; //Sparse table
std::pair<Query, std::pair<int, int>> Q2[MAX]; //Guarda las queries, su orden original y su respuesta
int LCAs[MAX]; //Guarda los LCAs
int currRes;
bool IncludeLCA[MAX]; //Nos indica si debemos incluir o no el LCA de cada Query
int log_2[MAX];


void DFS(int v){
    visitados[v] = 1; //Marca si esta visitado para la DFS
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
      ST[0][i] = i;

  //Creamos el resto de la tabla
  for (int j = 1; j <= n; j++)
    for (int i = 0; i + (1 << j) - 1 <= n; i++){
      //Compara las alturas pero ingresa los nodos
        if(alturas[ST[j-1][i]] < alturas[ST[j-1][i + (1 << (j - 1))]]){
          ST[j][i] = ST[j-1][i];
        }else{
          ST[j][i] = ST[j-1][i + (1 << (j - 1))];
        }
      }
}

int RanMQ(int a, int b){
    if(b < a)
        std::swap(a, b);

    int k = log_2[b-a+1];
    int x = ST[k][a];
    int y = ST[k][b - (1 << k) + 1];
    return (alturas[x] <= alturas[y])?x:y;
}

int LCA(int n1, int n2){
  int a = prim_visita[n1];
  int b = prim_visita[n2];
  return eulerTour[RanMQ(a, b)];
}

void agrega(int n){
  int aux = 0;
  if(cantidades[valores[n]] == 3)
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
    if(cantidades[valores[n]] == 3 && aux == 0){
      currRes++;
    }
  }
}

bool ordena_q(std::pair<Query, std::pair<int, int>>  x, std::pair<Query, std::pair<int, int>>  y){
    //Ordena por bloques primero
    if (x.first.L/block != y.first.L/block)
        return x.first.L/block < y.first.L/block;

    //Si estan en el mismo bloque ordena por el valor de R
    return x.first.R < y.first.R;
}

//Reordena para la impresion
bool ordena_print(std::pair<Query, std::pair<int, int>>  x, std::pair<Query, std::pair<int, int>>  y){

    return (x.second).first < (y.second).first;
}

//Calcula las queries una vez ordenadas
void queryResults(int N, int Q){

    // Inicializamos L, R y la respuesta actual
    int currL = 0, currR = 0;
    int L, R;
    // Recorremos las queries
    for (int i = 0; i < Q; i++){
        L = Q2[i].first.L;
        R = Q2[i].first.R;
        // Quitamos lo que no es necesario en la query
        while (currL < L){
            agrega(arbolDFS[currL]);
            currL++;
        }

        // Agregamos los elementos de la izquierda
        while (currL > L){
            currL--;
            agrega(arbolDFS[currL]);
        }

        while (currR < R){
            currR++;
            agrega(arbolDFS[currR]);
        }

        while (currR > R){
            agrega(arbolDFS[currR]);
            currR--;
        }


        int LCa = LCA(arbolDFS[Q2[i].first.L], arbolDFS[Q2[i].first.R]);

        if(IncludeLCA[(Q2[i].second).first]){
            agrega(LCa);
            std::cout << "si" << '\n';
        }

        (Q2[i].second).second = currRes;

        if(IncludeLCA[(Q2[i].second).first]){
            agrega(LCa);
        }

    }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N, Q, l, r;
  std::cin >> N;

  int Lsize = eulerTour.size();
  for(int i = 2; i < Lsize + 2; i++)
      log_2[i] = log_2[i/2] + 1;

  for (int i = 0; i < N; i++)
    std::cin >> valores[i];

  padres[0] = 0;
  alturas[0] = 0;

  for (int i = 1; i < N; i++){
    std::cin >> padres[i];
		hijos[padres[i]].push_back(i);
  }

  //Crea las linealizaciones necesarias
  DFS(0);
  //Define el tamanio del bloque
  block = floor(sqrt(arbolDFS.size()));


  std::cin >> Q;
  Query Queries[Q];
  for (int i = 0; i < Q; i++)
    std::cin >> Queries[i].L >> Queries[i].R;


  int n = eulerTour.size();
  construye_STable(n); //Para los LCAs

  //Acomoda las queries segun como se encuentren en la linealizacion
  //y si estan en el caso donde contienen al LCA
  for (int i = 0; i < Q; i++){
    LCAs[i] = LCA(Queries[i].L, Queries[i].R);
    std::cout << "LACs[i]"<< LCAs[i] << '\n';
    (Q2[i].second).first = i;
    if(LCAs[i] == eulerTour[Queries[i].L] || LCAs[i] ==  eulerTour[Queries[i].L] ){
          if(first[Queries[i].L] > first[Queries[i].R])
            std::swap(Queries[i].L, Queries[i].R);
          Q2[i].first.L = first[Queries[i].L];
          Q2[i].first.R = first[Queries[i].R];
          IncludeLCA[i] = false;
    }else{
          if(last[Queries[i].L] < first[Queries[i].R])
            std::swap(Queries[i].L, Queries[i].R);
          Q2[i].first.L = last[Queries[i].L];
          Q2[i].first.R = first[Queries[i].R];
          IncludeLCA[i] = true;
          std::cout << "ei" << '\n';
    }
  }

  //Ordenamos las queries segun como se pide en el algoritmo de Mo
  std::sort(Q2, Q2 + Q, ordena_q);

  //Calculamos los resultados de las queries
  queryResults(N, Q);

  //Ordenamos segun como nos llegaron las queries
  std::sort(Q2, Q2 + Q, ordena_print);

  //Imprimimos los resultados
  for (int i = 0; i < Q; i++)
    std::cout << (Q2[i].second).second   << '\n';


  return 0;
  }