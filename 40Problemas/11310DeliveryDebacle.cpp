#include<bits/stdc++.h>
#define ll long long
ll DP[41];

unsigned ll resuelve_DP(int n){
  if(n < 0)
      return 0;
  else if(DP[n] != 0)
      return DP[n];
  else //Si no lo hemos calculado lo calculamos
      return DP[n] = resuelve_DP(n-1) + 4*resuelve_DP(n-2) + 2*resuelve_DP(n-3);
      //+ resuelve_DP(n-1) pues podemos agregar uno de tamanno uno al final
      // + resuelve_DP(n-2) pues podemos agregar 4 distintos de tamanno dos al final
      // + resuelve_DP(n-3) pues podemos agregar 2 distintos de tamanno tres al final
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  DP[0] = 1; //Solo hay una forma de llenar una caja vacia
  DP[1] = 1;
  DP[2] = 5;
  ll N;
  ll num_casos;
  std::cin >> num_casos;
  while(num_casos--){
    std::cin >> N;
    std::cout << resuelve_DP(N) << '\n';
  }
  }
