#include<bits/stdc++.h>
#define ll long long
ll DP[70][70][2]; //Representa [n_cajones][n_asegurados][1 si el de hasta arriba asegurado]


/*Tenemos dos casos, el de hasta arriba esta asegurado o no. Nuestra respuesta
es la suma de estos casos.
Si el de hasta arriba esta asegurado solo necesitamos ver n-1 cajones y contar s-1 asegurados.
Si el de hasta arriba no esta asegurado, podemos asegurar el siguiente y buscar con
i-1 cajones en el caso de que la "tapa" esta puesta o buscar en i-1 sin la "tapa" puesta
*/
void forma_DP(){
  DP[1][1][1] = 1;
  DP[1][0][0] = 1;
  for (int i = 2; i <= 65; i++){
    DP[i][0][0] = DP[i-1][1][1] + DP[i-1][0][0];
    for (int j = 1; j <= i; j++){
      DP[i][j][0] = DP[i-1][j+1][1] + DP[i-1][j][0];
      DP[i][j][1] = DP[i-1][j-1][0] + DP[i-1][j-1][1];
    }
  }
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  forma_DP();
  int n, s;
  std::cin >> n >> s;
  while (n >= 0 && s>= 0) {
    std::cout << DP[n][s][0] + DP[n][s][1] << '\n';
    std::cin >> n >> s;
  }
    return 0;
  }
