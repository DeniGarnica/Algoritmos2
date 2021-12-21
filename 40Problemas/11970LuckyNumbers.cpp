#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ll num_casos, n, caso = 0;
  std::cin >> num_casos;
  for (ll i = 0; i < num_casos; i++) {
    std::cin >> n;
    std::cout << "Case "<<i+1<<":";
    ll x, raiz = sqrt(n)-1;
    for (ll j = raiz; j >= 1; j--) {
      x = n-j*j;
      if(x%j == 0 && x>0){
        std::cout << " "<<x;
      }
    }
    std::cout  << '\n';
  }
    return 0;
  }

/* Explicacion:
   Notemos que para que x sea entero, x<n. Por lo que podemos ecribir n-k = x.
   Pero queremos que sqrt(n-(n-k)) sea entero, lo cual solo pasara si k=j^2.
   Asi que tenemos la ecuacion (n-j^2)/j, la cual queremos que sea etero.
   Por lo que se cumple si (n-j^2)%j == 0.
   j<sqrt(n) pues n-j^2 debe ser mayor a 0.
*/
