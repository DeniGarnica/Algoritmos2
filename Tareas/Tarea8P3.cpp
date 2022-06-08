#include<bits/stdc++.h>
#define ll long long
#define MAX 1010
ll m = 1000000007; //Con este valor de m la probabilidad de colision es muy baja
ll p[MAX]; //Arreglo de potencias del primo
ll h[MAX][MAX]; //hash del string que incia en i y termina en j,

//Precalcula las potencias del primo
void p_i(int prime, int n){
  p[0] = 1;
  for (int i = 1; i < n; i++)
    p[i] = p[i-1]*prime;
}

//Calcula el hash de manera manual
ll hash(std::string &s, int i, int j){
  if(h[i][j] == 0)
    return h[i][j];
  ll res = 0;
  for (int k = i; k <= j; k++)
    res += (p[k-i]*(s[k] - 'A' + 1))%m;
  h[i][j] = res;
  return res;
}

//Nos devuelve el h(s[i,j])p^i mod m en O(1)
ll hash_p_i(int i, int j){
  return (h[0][j] - h[0][i-1])%m;
}

//Precalcula todos los hash de todos los prefijos en O(n)
void rolling_hash_prefijos(std::string &s){
  int n = s.size();
  h[0][0] = (s[0] - 'A' + 1)%m;
  for (int i = 1; i < n; i++){
    h[0][i] =  (h[0][i-1] + (s[0] - 'A' + 1)*p[i])%m;
  }
  return;
}

//Precalcula todos los hash de todos los sufijos en O(n)
void rolling_hash_sufijos(std::string &s){ //
  int n = s.size();
  h[n-1][n-1] = (s[n-1] - 'A' + 1)%m;
  for (int i = n-2; i >= 0; i--){
    h[i][n-1] =  (h[i+1][n-1]*p[1] + (s[i] - 'A' + 1))%m;
  }
  return;
}

//Calcula el hash de un substring usando el anterior
//Le pasasmos el hash de s[i][j] y calcula el de s[i-1][j-1]
//Es decir, conserva el tama;o, solo se mueve una posicion a la izq
ll rolling_hash(std::string &s, int h_ant, int i, int j){
  h[i-1][j-1] =  ((s[i-1] - 'A' + 1) + p[1]*(h_ant - (s[j] - 'A' + 1)*p[j-i]))%m ;
  return h[i-1][j-1];
}

//Pre-calcula los hash de todos los posibles substrings de tamano i
void hash_substring_i(std::string &s, int i){
  int n = s.size();
  ll auxi;
  ll h_actual;
  h_actual = h[n-i][n-1]; //Este ya lo precalculamos anteriormente
  //Iremos calculando los hash de tama;o i con rolling hashing
  for (int j = n-1; j >= i; j--)
    h_actual = rolling_hash(s, h_actual, j-i+1 ,j);
  return;
}

int respuesta(std::string &s, int mayor, int k, int n){
  for (int i = mayor; i >= 1 ; i--){
    hash_substring_i(s, i);
    for (int j = 0; j <= n - i*k; j++) {
      for (int l = 0; l < k-1; l++) {
        if(h[j + l*i][j + (l+1)*i - 1] != h[j + (l+1)*i][j + (l+2)*i - 1])
          break;
        if(l == k-2)
          return i*k;
      }
    }
  }
  return 0;
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos, k, res;
  std::string s;
  std::cin >> num_casos;
  for (int m = 0; m < num_casos; m++) {
    memset(h, 0, sizeof(h));
    std::cin >> k >> s;
    int n = s.size();
    if(k == 1){
      std::cout << n << '\n';
    }else{
      p_i(33, n+3);
      rolling_hash_sufijos(s);
      int mayor = ceil(n/k);
      int res = respuesta(s, mayor, k, n);
      std::cout << res << '\n';
    }
  }

  return 0;
}
