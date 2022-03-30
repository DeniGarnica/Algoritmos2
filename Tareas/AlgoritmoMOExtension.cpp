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
int prim_visita[MAX]; //Marca la 1a visita en el euler Tour
int cantidades[5005]; //Nos guarda cuantas veces aparece cada numero
bool process[MAX]; //Nos almacena si ya esta o no metido el nodo
int orden[MAX]; //Tendra el orden de los nodos en el arbol linealizado
int block;

struct Query{
    int L, R;
};

void DFS(int v){
    visitados[v] = 1;
    prim_visita[v] = eulerTour.size();
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

//Esta funcion nos devuelve la respuesta una vez tenemos el intervalo
int cuenta(int l, int r){
  int res = 0;
  for (int i = l; i < r; i++)
    if(cantidades[i] >= 3)
      res++;
  return res;
}

bool ordena_visita(int a, int b){
  return prim_visita[a] < prim_visita[b];
}


bool ordena_q(Query x, Query y){
    //Ordena por bloques primero
    if (orden[x.L]/block != orden[y.L]/block)
        return orden[x.L]/block < orden[y.L]/block;

    //Si estan en el mismo bloque ordena por el valor de R
    return orden[x.R] < orden[y.R];
}

/*void queryResults(int N, Query &q, int Q){

    // Empezamos ordenando las queries
    sort(q, q + Q, ordena_q);

    // Inicializamos L, R y la respuesta actual
    int currL = 0, currR = 0;
    int currRes = cuenta(q[0].L, q[0].R);



    // Recorremos las queries
    for (int i = 0; i < m; i++){

        // Quitamos lo que no es necesario en la query
        while (currL < q[i].L){
            currRes -= a[currL];
            currL++;
        }

        // Add Elements of current Range
        while (currL > q[i].L)
        {
            currRes += a[currL-1];
            currL--;
        }
        while (currR <= q[i].R)
        {
            currRes += a[currR];
            currR++;
        }

        // Remove elements of previous range.  For example
        // when previous range is [0, 10] and current range
        // is [3, 8], then a[9] and a[10] are subtracted
        while (currR > q[i].R+1)
        {
            currRes -= a[currR-1];
            currR--;
        }

        // Print sum of current range
        cout << "Sum of [" << q[i].L << ", " << q[i].R
             << "] is "  << currSum << endl;
    }
}*/


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

  block = floor(sqrt(N));
  std::sort(orden, orden + N, ordena_visita); //Ordena que nodos estan primero en el arreglo linealizado

  std::cin >> Q;
  Query Queries[Q];
  for (int i = 0; i < Q; i++)
    std::cin >> Queries[i].L >> Queries[i].R;

  for (int i = 0; i < Q; i++){
    int aux;
    if(prim_visita[Queries[i].L] > prim_visita[Queries[i].R]){
      aux = Queries[i].L;
      Queries[i].L = Queries[i].R;
      Queries[i].R = aux;
    }
  }

  std::sort(Queries, Queries + Q, ordena_q);

  for (int i = 0; i < Q; i++)
    std::cout << "(" <<Queries[i].L << ","<< Queries[i].R << ")" << '\n';


  return 0;
  }
