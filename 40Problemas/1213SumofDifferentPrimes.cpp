#include<bits/stdc++.h>
#define ll long long
#define MAX 1500 
ll arr[MAX];
std::vector<ll> primos;
ll N, k;
ll dp[MAX][20][200];

void criba(){
  arr[1]=1;
  arr[2]=0;
  for (ll i = 2; i < MAX; i++) {
    if(arr[i] == 0){
      primos.push_back(i);
      for (ll j = i*i; j < MAX; j+=i)
        arr[j] = 1;
    }
  }
}

ll resuelve(ll N, ll k, ll i){
  if (N > 0 && k == 0) return 0;
  if (N == 0 && k == 0) return 1;
  if (primos[i] > N) return 0;
  //if(N < 0 || k < 0) return 0;
  if (dp[N][k][i] != -1) return dp[N][k][i];
  return dp[N][k][i] = resuelve(N - primos[i], k-1, i+1) + resuelve(N, k, i+1);
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  criba();
  memset(dp, -1, sizeof dp);
  std::cin >> N >> k;
  while (N || k) {
    std::cout << resuelve(N, k, 0) << std::endl;
    std::cin >> N >> k;
  }
    return 0;
}
