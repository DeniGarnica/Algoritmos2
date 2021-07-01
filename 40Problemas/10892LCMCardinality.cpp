#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

ll p[150001]; //guarda primos en orden
bool A[150001];

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

void primos(){
  ll cont = 0;
  for (size_t i = 2; i < 150001; i++) {
    //std::cout << "i: "<< i << '\n';
    if(!A[i]){ //si no es compuesto
      p[cont]=i;
      cont++;
    }
    for(ll j = 0; j < cont && p[j]*i<150001; j++){
      //std::cout << "i*p[j]: "<<i*p[j] << '\n';
      A[i*p[j]] = 1; // a los compuestos de los primos hasta ahora generados les asigna 1
      if (i%p[j]==0) //Si llegamos al mismo numero o su potencia 
        break;
    }
  }
}

ll descomposicion(int n){

}

int main(){
  primos();
  ll n;
  std::cin >> n;
  while (n!=0) {
    if(n==1){
      std::cout << n <<" "<<1 << '\n';
    }else{
      //ll res =  descomposicion(n);
      ll res = 1;
      std::cout << n <<" "<< res/2 + 1 << '\n';
    }
    std::cin >> n;
  }
  return 0;
}
