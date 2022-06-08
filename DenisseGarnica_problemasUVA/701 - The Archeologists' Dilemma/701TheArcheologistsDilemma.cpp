//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long

/*
Buscamos una potencia p de 2,  tal que sus primeros digitos sean los  mismos que
el input N. Sea T la cantidad de digitos distintos entre 2^p y n, notemos que si
encontramos un valor de p, entonces cumple la ecuacion piso(2^p/10^t) = n. Con
esta ecuacion podemos llegar a la desigualdad
n <= 2^p/10^t < n+1, y de ahi ver que
log_2(n) + Tlog_2(10) <= p < log_2(n+1) + tlog_2(10)
por lo que necesitamos encontrar un valor p que satisfaga ambas
*/


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string aux;
  int n; double x, y; double log10 = log(10)/log(2);
  while(std::cin>>aux){
    int s = aux.size()+1;
    n = std::stoi(aux);
    while(1){
      x = log(n)/log(2) + (s)*log10;
      y = log(n+1)/log(2) + (s)*log10;

      if((int)x < (int)y) break;
      s++;
    }
    std::cout << ceil((int)x + 1) << std::endl;
  }
    return 0;
  }
