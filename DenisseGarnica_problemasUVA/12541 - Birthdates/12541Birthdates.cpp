//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos, dia, mes, year;
  std::string name, n_mayor, n_menor;
  std::cin >> num_casos;
  int mayor = 0; int menor = 1000000000;
  ll actual;
  for (int i = 0; i < num_casos; i++){
    std::cin >> name >> dia >> mes >> year;
    //le daremos mas peso al year, despues al mes y por ultimo al dia
    actual = dia + mes*100 + year*1000;
    //guardamos el mayor y menor actual
    if(mayor < actual){
      mayor = actual;
      n_mayor = name;
    }
    if(menor > actual){
      menor = actual;
      n_menor = name;
    }
  }
  //imprimos los resultados
  std::cout << n_mayor << '\n';
  std::cout << n_menor << '\n';
  return 0;
}
