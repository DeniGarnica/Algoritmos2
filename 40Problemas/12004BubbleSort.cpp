#include<bits/stdc++.h>
#define ll long long

/* Ya que los numeros son random, la probabilidad de que el b[j] > b[j+1]
es la misma que el caso contrario. Por lo que el valor esperado del swap
es 1/2
Vemos que todas las formas posibles de tomar dos numeros distintos de los n
es C(n, 2) = n!/((n-2)!2!) = [(n-2)!(n-1)n]/((n-2)!2!) = (n-1)*n/2
Y como mencionamos el valor esperado del swap es 1/2, por lo que el valor
esperado final es (n-1)*n/4. (n-1)*n ya es par, por lo que solo es necesario ver
si es divisible entre 4 o no.
*/

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos;
  ll n;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++){
    std::cin >> n;
		n *= (n-1); //Ya sabemos que este numero es par
		std::cout << "Case "<<i+1<<": ";
		if (n%4 != 0) std::cout << n/2<<"/2" << '\n';
    else std::cout << n/4 << '\n';
  }
  }
