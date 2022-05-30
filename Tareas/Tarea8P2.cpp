#include<bits/stdc++.h>
#define ll long long
#define MAX 1010
ll m = 1000000007; //Con este valor de m la probabilidad de colision es muy baja
ll p[MAX]; //Arreglo de potencias del primo
ll h[MAX][MAX]; //hash del string que incia en i y termina en j
bool nd[30]; //indica si son caracteres no deseados donde nd[0] marca si 'a' es no deseado
int cant_nd[MAX]; //Guarda la cantidad de caracteres no deseados de cada sufijo

//Precalcula las potencias del primo
void p_i(int prime, int n){
  p[0] = 1;
  for (int i = 1; i < n; i++)
    p[i] = p[i-1]*prime;
}

//Precalcula todos los hash de todos los sufijos en O(n)
//Calcularemos cuantos caracteres no deseados tiene cada sufijo
void rolling_hash_sufijos(std::string &s){
  int n = s.size();
  h[n-1][n-1] = (s[n-1] - 'a' + 1)%m;
  cant_nd[n-1] = nd[s[n-1] - 'a']; //solo le es necesario ver si el ultimo caracter es no deseado
  for (int i = n-2; i >= 0; i--){
    //Solo es necesario ir agregando una letra
    cant_nd[i] = cant_nd[i+1] + nd[s[i] - 'a'];
    h[i][n-1] =  (h[i+1][n-1]*p[1] + (s[i] - 'a' + 1))%m;
  }
  return;
}

//Calcula el hash de un substring usando el anterior en O(1)
//Le pasasmos el hash de s[i][j] y calcula el de s[i-1][j-1]
//Es decir, conserva el tama;o, solo se mueve una posicion a la izq
//Tambien le pasamos la cantidad de no deseados del anterior para calcular de este
//devuelve la cantidad de no deseados
int rolling_hash(std::string &s, int h_ant, int i, int j, int cant_nd_ant){
  int res = cant_nd_ant + nd[s[i-1] - 'a'] - nd[s[j] - 'a'];
  h[i-1][j-1] =  ((s[i-1] - 'a' + 1) + p[1]*(h_ant - (s[j] - 'a' + 1)*p[j-i]))%m ;
  return res;
}

//Calcula los hash de todos los posibles substrings de tamano i
//devuelve la cantidad de distintos con menos de k carcateres no deseados
int hash_substring_i(std::string &s, int i, int k){
  int n = s.size();
  ll auxi; //Guardaremos el valor mas alto del bucket
  ll h_actual; //Guardamos el has actual para usar en el rolling hash
  int nd_actual;
  int res = 0;
  std::unordered_map<ll, int> bucket;
  //Este ya esta calculado por que es un sufijo y tenemos la funcion de precarculo de sufijos
  nd_actual = cant_nd[n-i]; //cantidad de no deseados de la cadena actual
  h_actual = h[n-i][n-1];
  bucket[h_actual] = 1; //Falta calcular si este tiene caracteres no deseados
  if(nd_actual <= k) //Si eran menos de k, se suma a la respuesta
    res++;

  for (int j = n-1; j >= i; j--) {
    //Iremos calculando los hash de tama;o i con rolling hashing
    //y tambien la cantidad de no deseados de la cadena
    nd_actual = rolling_hash(s, h_actual, j-i+1 ,j, nd_actual);
    auxi = h[j-i][j-1] ; //El hash que se acaba de calcular
    if (bucket.find(auxi) == bucket.end()){ //Si es la primera repeticion de esta cadena
      bucket[auxi] = 1;
      if(nd_actual <= k) //y si eran menos de k, se suma a la respuesta
        res++;
    }
    h_actual = auxi;
  }
  return res;
}

//Llena el arreglo de caracteres no deseados de los sufijos
void no_deseados(std::string &s){
  int n = s.size();
  int aux;
  for (int i = 0; i < n; i++){
    aux = (s[i] - 'a');
    nd[aux] = 1;
  }
  return;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string n_d, s;
  int k;
  int res = 0;
  std::cin >> n_d >> k >> s;
  int n = s.size();
  p_i(33, n+3); //Precalculamos los primos
  no_deseados(n_d); //Marcamos los caracteres no deseados
  rolling_hash_sufijos(s); //Calculamos los hash de los sufijos
  for (int i = 1; i <= n; i++)
    res += hash_substring_i(s, i, k);
  std::cout << res << '\n';
  }
