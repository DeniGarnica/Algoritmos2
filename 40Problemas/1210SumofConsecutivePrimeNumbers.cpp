#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll primos[100001];
vector<ll>primes;
ll lon;

void num_primos(){ //Primero usamos una criba para generar los numeros primos.
  primos[1]=1;
  primos[2]=1;
  for (ll i = 3; i < 10001; i++) {
    primos[i]=1;
  }
  for (ll i = 2; i < 10001; i++) {
    if(primos[i]==1){
      primes.push_back(i);
      for (ll j = i*i; j < 10001; j+=i) {
        primos[j] = 0;
      }
    }
  }
  lon = primes.size();
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  num_primos(); //Corremos la criba
  ll num, cont, suma;
  std::cin >> num;
  while (num) { //Mientras el numero ingresado sea distinto de cero
    cont = 0;  //REiniciamos la cuenta
    for (ll i = 0; primes[i]<=num; i++){ //Como maximo odemos llegar a un primo menor igual al numero
      suma = primes[i]; //Iniciamos la suma en el primo
      for (ll j = i+1;  suma < num; j++) //Vamos sumando los siguientes primos.
        suma+=primes[j];
      if(suma==num) 
        cont++;
    }
    std::cout << cont << '\n';
    std::cin >> num;
  }
    return 0;
  }
