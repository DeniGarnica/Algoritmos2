//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#include <map>
using namespace std;
#define ll long long
map<ll, ll> mapa;
map<ll, ll> mapa2;

//Idea: creamos un map con cada una de las cartas de A y B
//Despues solo buscamos en orden si la carta actual esta en el mazo de la otra
//si no lo esta sumamos uno a la respuesta parcial
//Al final devolvemos el minimo de las respuestas parciales

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ll dato1, dato2, aux, cont1, cont2, uno;
  std::cin >> dato1>> dato2;
  while(dato1!=0 && dato2 != 0){
    for (ll i = 0; i < dato1; i++) {
      cont1=0;
      cont2=0;
      std::cin >> aux;
      if (mapa.find(aux) == mapa.end()) {
        uno = 1;
        mapa.insert(pair<ll, ll>(aux, uno));
      }else{
          mapa[aux]++;
      }
    }
    for (ll i = 0; i < dato2; i++) {
      std::cin >> aux;
      if (mapa2.find(aux) == mapa2.end() ) {
          mapa2.insert(pair<ll, ll>(aux, uno));
      }else{
          mapa2[aux]++;
      }
    }
    for (map<ll, ll>::iterator it = mapa.begin(); it != mapa.end(); ++it){
      aux = it->first;
      if (mapa2.find(aux) == mapa2.end()){
        cont1++;
      }
    }
    for (map<ll, ll>::iterator it = mapa2.begin(); it != mapa2.end(); ++it){
      aux = it->first;
      if (mapa.find(aux) == mapa.end()){
        cont2++;
      }
    }
    std::cout <<min(cont1, cont2) << '\n';
    std::cin >> dato1>> dato2;
    mapa.clear();
    mapa2.clear();
  }

    return 0;
  }
