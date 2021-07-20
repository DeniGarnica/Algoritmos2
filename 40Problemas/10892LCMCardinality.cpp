#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

ll p[90000000]; //guarda primos en orden
bool A[90000000];

ll gcd(ll a, ll b){
  ll g;
    if (a == 0)
       return b;
    if (b == 0)
       return a;
    if (a == b)
        return a;
    if (a > b){
      while (a-b>b) {
        a=a-b;
      }
      g = gcd(a-b, b);
      return g;
    }
    while (b-a>a) {
      b=b-a;
    }
    g = gcd(a, b-a);
    return g;
}

ll contp = 0;
ll primos(ll x){
  for (size_t i = 2; i < 90000000; i++) {
    //std::cout << "i: "<< i << '\n';
    if(!A[i]){ //si no es compuesto
      p[contp]=i;
      cont++;
    }
    for(ll j = 0; j < contp && p[j]*i<90000000; j++){
      //std::cout << "i*p[j]: "<<i*p[j] << '\n';
      A[i*p[j]] = 1; // a los compuestos de los primos hasta ahora generados les asigna 1
      if (i%p[j]==0) //Si llegamos al mismo numero o su potencia
        break;
    }
  }
}

ll descomposicion(int n){
  ll k=0,cont,res=1;
  while(n>1){
      cont=0;
      while(n%p[k]==0){
          n/=p[k];
          cont++;
      }
      res*=(cont*2)+1;
      k++;
  }
  return res;
}

int main(){
  primos();
  ll n;
  std::cin >> n;
  while (n!=0) {
    if(n==1){
      std::cout << n <<" "<<1 << '\n';
    }else{
      ll res =  descomposicion(n);
      std::cout << n <<" "<< res/2 + 1 << '\n';
    }
    std::cin >> n;
  }
  return 0;
}
