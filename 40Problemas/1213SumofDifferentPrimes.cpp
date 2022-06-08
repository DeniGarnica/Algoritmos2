//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long
#define MAX 1500
ll arr[MAX];
std::vector<ll> primos;
ll N, k;
//DP[n][k][i] = expresar al numero n como la suma de k primos usando el primo i esimo
ll dp[MAX][20][200];

void criba(){ //precalculamos los primos
  arr[1]=1;
  arr[2]=0;
  for (ll i = 2; i < MAX; i++) {
    if(arr[i] == 0){
      primos.push_back(i); //guardamos los primos ordednados
      for (ll j = i*i; j < MAX; j+=i)
        arr[j] = 1;
    }
  }
}

//usaremos una dp
ll resuelve(ll N, ll k, ll i){
  if (N > 0 && k == 0) return 0;
  if (N == 0 && k == 0) return 1;
  if (primos[i] > N) return 0;
  //si ya lo hemos calculado solo lo devuelve
  if (dp[N][k][i] != -1) return dp[N][k][i];
  //expresar al numero n como la suma de k primos usando el primo i esimo es lo
  //lo mismo a calcular las maneras de expresar a n como la suma de k primos
  //usando a partir del primo i+1-esimo
  //mientras que resuelve(N - primos[i], k-1, i+1) nos dice que si uso el primo
  //i-esimo, por ello se lo restamos al N
  //por lo que el resultado es la suma de haber usado el primo i esimo y el no haberlo usado
  return dp[N][k][i] = resuelve(N - primos[i], k-1, i+1) + resuelve(N, k, i+1);
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  criba();
  memset(dp, -1, sizeof dp); //prellenamos de -1 los valores
  std::cin >> N >> k;
  while (N || k) {
    //empezamos la dp dede el primo en la posicion 0.
    std::cout << resuelve(N, k, 0) << std::endl;
    std::cin >> N >> k;
  }
    return 0;
}
