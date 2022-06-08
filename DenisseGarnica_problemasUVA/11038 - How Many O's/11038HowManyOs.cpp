//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx


#include<bits/stdc++.h>
#define ll long long

ll num_zeros(ll n){
  if(n<0) return 0;
	ll res = 1; //empezamos contando el 0
	ll n_10 = 1; ll cola = 0;
	while(n){
    //Si no termina en 0 cuenta la cantidad de ceros de los multiplos de 10 de
    //la potencia actual y los multiplica por la cantidad de veces que esa potencia
    //se va a repetir
		if(n%10 != 0)
			res += n/10*n_10;
    //si termina en 0 ve cuantos ceros hay en medio ejemplo 101 tiene un 0 en medio
		else
			res += (n/10-1)*n_10 + (cola+1);
    //guaradamos los residuos que se perdieron al dividir para contar los ceros de en medio
		cola += n%10*n_10;
		n /= 10; n_10 *= 10;
	}
	return res;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  ll m, n;
  std::cin >> m >> n;
  while(m >= 0 && n >= 0){
    //cantidad de 0s de la cota superior, menos cantidad de 0s de la cota inferior
    std::cout << num_zeros(n) - num_zeros(m-1) << '\n';
    std::cin >> m >> n;
  }


    return 0;
}
