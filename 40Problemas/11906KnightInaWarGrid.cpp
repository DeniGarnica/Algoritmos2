#include<bits/stdc++.h>
#define ll long long
typedef std::pair<int, int> pair;
//std::vector<pair> adyacencia[101][101]; //Nos dice los hijos del nodo[i][j]
bool V[101][101]; //Marcamos los visitados
bool A[101][101]; //Marcamos los visitados
int M, N, R, C;
int par, impar;


void BFS(int x, int y){
    std::queue<pair> q;
    V[x][y] = 1;
    pair aux; aux.first = x; aux.second = y;
    q.push(aux);

    while(!q.empty()){
        pair s = q.front(); //EL nodo que estamos viendo
        x = s.first; y = s.second;
        //std::cout << "V "<<x<<", "<< y << '\n';
        q.pop();
        //V[x][y] = 1; //Marcamos como visitado

        int D_x[8] = {M, N, -M, -N, M, N, -M, -N};
        int D_y[8] = {N, M, -N, -M, -N, -M, N, M};
        int aristas = 0;
        for (int i = 0; i < 8; i++){
          if(x + D_x[i] >= 0 && x + D_x[i] < R && y + D_y[i] >= 0 && y + D_y[i] < C){ //Vemos que no se salga de la matriz
              pair auxi; auxi.first = x + D_x[i]; auxi.second = y + D_y[i];
              if(!A[auxi.first][auxi.second])
                aristas++;
              if(!V[auxi.first][auxi.second]){
                V[auxi.first][auxi.second] = 1; //Marcamos como visitado
                q.push(auxi); //Agregamos el hijo a la cola
              }
          }
        }

        if(M == 0 || N == 0 || M == N) aristas/=2;
        if(aristas!=0 && aristas%2 == 0) par++;
        else if(aristas!=0) impar++;

    }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos, n_w, x, y;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    memset(V, 0, sizeof(V));
    memset(A, 0, sizeof(A));
    std::cin >> R >> C;
    std::cin >> M >> N; //Tipo de pasos
    std::cin >> n_w;
    par = 0; impar = 0;
    for (int j = 0; j < n_w; j++){
      std::cin >> x >> y;
      A[x][y] = 1; //Marcamos como agua
      V[x][y] = 1;
    }
    BFS(0,0);
    std::cout << "Case "<< i+1<<": "<<par <<" "<<impar << '\n';

  }
  }
