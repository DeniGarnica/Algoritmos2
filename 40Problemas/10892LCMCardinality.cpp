#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

ll p[150001];
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
    if(!A[i])
      p[cont++]=i;
    for(ll j = 0; j < cont && p[j]*i<150001; j++){
      A[i*p[j]] = 1;
      if (i%p[j]==0)
        break;
    }
  }
}

ll descomposicion(int n){

}

int main(){
  primos();
  for (size_t i = 0; i < 100; i++) {
    std::cout << p[i] << '\n';
  }
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
