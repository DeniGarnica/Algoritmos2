#include<bits/stdc++.h>
#define ll long long
#define MAX 1010
ll m = 1000000007; //Con este valor de m la probabilidad de colision es muy baja
ll p[MAX]; //Arreglo de potencias del primo
ll h[MAX][MAX]; //hash del string que incia en i y termina en j,
int val = 0;

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
    res += (p[k-i]*(s[k] - val + 1))%m;
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
  h[0][0] = (s[0] - val + 1)%m;
  for (int i = 1; i < n; i++){
    h[0][i] =  (h[0][i-1] + (s[0] - val + 1)*p[i])%m;
  }
  return;
}

//Precalcula todos los hash de todos los sufijos en O(n)
void rolling_hash_sufijos(std::string &s){ //
  int n = s.size();
  h[n-1][n-1] = (s[n-1] - val + 1)%m;
  for (int i = n-2; i >= 0; i--){
    h[i][n-1] =  (h[i+1][n-1]*p[1] + (s[i] - val + 1))%m;
  }
  return;
}

//Calcula el hash de un substring usando el anterior
//Le pasasmos el hash de s[i][j] y calcula el de s[i-1][j-1]
//Es decir, conserva el tama;o, solo se mueve una posicion a la izq
ll rolling_hash(std::string &s, int h_ant, int i, int j){
  //std::cout << "h_actual = "<< h_ant << '\n';
  //std::cout << "(s[i-1] - val + 1) "<< (s[i-1] - val + 1) << '\n';
  //std::cout << "(s[j] - val + 1)*p[j-i] = ("<< s[j] - val + 1<<")*"<<p[j-i] << '\n';
  h[i-1][j-1] =  ((s[i-1] - val + 1) + p[1]*(h_ant - (s[j] - val + 1)*p[j-i]))%m ;
  return h[i-1][j-1];
}

//Pre-calcula los hash de todos los posibles substrings de tamano i
void hash_substring_i(std::string &s, int i){
  int n = s.size();
  ll auxi;
  ll h_actual;
  h_actual = h[n-i][n-1]; //Este ya lo precalculamos anteriormente
  //std::cout << "sufijo = h["<<n-i<< "]["<<n-1<<"] = "<< h[n-i][n-1] << '\n';
  //Iremos calculando los hash de tama;o i con rolling hashing
  for (int j = n-1; j >= i; j--){
    h_actual = rolling_hash(s, h_actual, j-i+1 ,j);
    //std::cout << "h["<< j-i<<"]["<<j-1 <<"] = "<< h[j-i][j-1] << '\n';
  }

  return;
}

int respuesta(std::string &s, int mayor, int k, int n){
  int cont = 0;
  for (int i = mayor; i >= 1 ; i--){
    //std::cout << "i: "<< i << " ";
    hash_substring_i(s, i);
    for (int j = 0; j <= n - i*k; j++) {
      for (int l = 0; l < k-1; l++) {
        //std::cout << "segundo h["<<j+(k-1)*l<<"]["<< i-1+j+(k-1)*l <<"] =? h["<<i+j+(k-1)*l<<"]["<<2*i-1+j+(k-1)*l<<"] " << '\n';
        //std::cout << h[j+k*l][i-1+j+k*l] << "   "<< h[i+j+k*l][2*i-1+j+k*l] << '\n';
        if(h[j+(k-1)*l][i-1+j+(k-1)*l] == h[i+j+(k-1)*l][2*i-1+j+(k-1)*l]){
          cont++;
          //std::cout << "si" << '\n';
        }else{
          break;
        }
        if(cont+1 >= k)
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
      if(s[0]<= 90) val = int('A');
      else val = int('a');
      rolling_hash_sufijos(s);
      int mayor = ceil(n/k);
      int res = respuesta(s, mayor, k, n);
      std::cout << res << '\n';
    }
  }

  return 0;
}
