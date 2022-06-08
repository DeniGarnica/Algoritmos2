#include<bits/stdc++.h>
#define ll long long
ll DP[100][100][100];

ll util_DP(std::string &a, std::string &b, std::string &c, ll x, ll y, ll z){
  ll n = a.size(); ll m = b.size(); ll p = c.size();
  if(z == p)
    return 1;
  if(DP[x][y][z] != -1)
    return DP[x][y][z];
  ll suma = 0;
  for (ll i = x; i < n; i++)
    if(a[i] == c[z])
      suma += util_DP(a, b, c, i+1, y, z+1);
  for (ll i = y; i < m; i++)
    if(b[i] == c[z])
      suma += util_DP(a, b, c, x, i+1, z+1);
  DP[x][y][z] = suma;
  return suma;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  ll num_casos, dato1, dato2;
  std::string a, b, c;
  std::cin >> num_casos;
  for (ll i = 0; i < num_casos; i++) {
    std::cin >> a >> b >> c;
    memset(DP,-1,sizeof(DP));
    std::cout << util_DP(a, b, c, 0, 0, 0) << '\n';

  }
    return 0;
  }
