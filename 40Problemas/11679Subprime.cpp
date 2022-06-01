#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int b, n, cobrador, pagador, cantidad;
  std::cin >> b>>n;
  while(b != 0 && n != 0){
    int dinero[b]; //Guarda su reserva mas lo que le deben y se resta lo que debe
    for (int i = 0; i < b; i++){
      std::cin >> dinero[i];
    }
    for (int i = 0; i < n; i++) {
      std::cin >> pagador >> cobrador >> cantidad;
      dinero[pagador-1] -= cantidad; 
      dinero[cobrador-1] += cantidad;
    }
    int res = 1;
    for (int i = 0; i < b; i++)
      if(dinero[i] < 0) res = 0; //Si alguno obtiene un balance negativo, no funciona


    if(res) std::cout << "S" << '\n';
    else std::cout << "N" << '\n';

    std::cin >> b>>n;
  }
    return 0;
  }
