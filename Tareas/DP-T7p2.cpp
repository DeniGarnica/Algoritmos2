#include<bits/stdc++.h>
#define ll long long
#define MAX 10000
bool DP[MAX][MAX]; //DP[i][j] nos dice si la cadena c hasta i+j+1 es una mezcla de a hasta i, y b hasta j

bool crea_DP(std::string &a, std::string &b, std::string &c){
  int n = a.size(); int m = b.size(); int p = c.size();
  if(n+m != p) //Si el tamano no coincide, ya sabemos que no es una mezcla
    return 0;

  //Vaciamos la matriz
  memset(DP, 0, sizeof(DP));

  DP[0][0] = 1; //Ambas cadenas estan vacias

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++) {
      if(i == 0 && j != 0) //Solo una de las cadenas tiene caracteres
        if(b[j-1] == c[j-1])
          DP[i][j] = DP[i][j-1];

      if(j == 0 && i != 0)
        if(a[i-1] == c[i-1])
          DP[i][j] = DP[i-1][j];

      if(i != 0 && j != 0){ //Ambas cadenas tienen caracteres
        if(a[i-1] == c[i+j-1] && b[j-1] != c[i+j-1])
          DP[i][j] = DP[i-1][j];
        if(b[j-1] == c[i+j-1] && a[i-1] != c[i+j-1] )
  				DP[i][j] = DP[i][j-1];
        if(b[j-1] == c[i+j-1] && a[i-1] == c[i+j-1]){
          if(DP[i][j-1]){
  				    DP[i][j] = DP[i][j-1];
          }else if(DP[i-1][j]){
              DP[i][j] = DP[i-1][j];
          }
        }
      }

    }

  return DP[n][m]; //Devolvemos el resultado de ambas cadenas completas

}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos, p, n, m;
  std::cin >> num_casos;
  std::string a, b, c;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> a >> b >> c;
    std::cout << crea_DP(a, b, c) << '\n';
  }
    return 0;
  }
