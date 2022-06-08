/*
Denisse Garnica Sanchez
denisse.garnica@cimat.mx
*/

#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int p, a, b, c, d, n;
  std::cout << std::setprecision(10);//Para la precision de decimales
  while (std::cin >> p >> a >> b >> c >> d >> n){
		double res = 0; double actual;
		double max = p*(sin((a + b)) + cos((c + d)) + 2);
		for (int i = 2; i <= n; i++){
      //vamos avaluando la funcion y buscando donde la diferencia es mayor
			actual = p * (sin((a * i + b)) + cos((c * i + d)) + 2);
				if (max > actual){
					if(res < max - actual) res = max - actual;
			  }else{
          max = actual;
		    }
    }
		std::cout << res << std::endl;
	}
    return 0;
  }
