//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N;
  //Creamos uin set y solo buscamos si el valor ingresado esta o no en el set
  //y eso define si es un numero especial o no.
  std::set<int> special = {1, 64, 729, 4096, 15625, 46656, 117649, 262144, 531441, 1000000,
  1771561, 2985984, 4826809, 7529536, 11390625, 16777216, 24137569, 34012224,
  47045881, 64000000, 85766121};
  std::cin >> N;
  while(N){
    auto pos = special.find(N);

    if(pos != special.end())
        std::cout << "Special" << '\n';
    else
        std::cout << "Ordinary" << '\n';

    std::cin >> N;
  }
    return 0;
  }
