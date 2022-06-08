//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int a, c, h_actual;
  std::cin >> a >> c;
  while(a != 0 && c != 0){
    int cont = 0;
    int h[c];
    std::cin >> h[0];
    cont = a - h[0];
    for (int i = 1; i < c; i++){
      std::cin >> h[i];
      //Solo es necesario agregar nuevos movimientos si el anterior tapa al siguiente
      //La cantidad de nuevos movimientos a agregar es la diferencia de por lo cuanto tapa
      if(h[i-1] > h[i])
        cont+= h[i-1]-h[i];
    }
    std::cout << cont << '\n';
    std::cin >> a >> c;
  }
    return 0;
  }
