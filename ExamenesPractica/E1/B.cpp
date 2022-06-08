#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  ll n, q, type_q;
  std::unordered_map<ll, ll> umap;
  std::cin >> n >> q;
  ll A[n]; ll todos = -1; ll index, x, aux; ll actual = 0;
  for (ll i = 0; i < n; i++){
    std::cin >> A[i];
    actual += A[i];
  }
  for (ll i = 0; i < q; i++){
    std::cin >> type_q;
    if(type_q == 1){
      std::cin >> index >> x;
      index--;
      if (todos != -1 && umap.find(index) == umap.end()) //Si no esta en el mapa y alguna vez hemos modificado todo el arreglo
        aux = todos;
      else //Si esta en el map o nunca hemos modificado todos
        aux = A[index];
      A[index] = x;
      if(todos != -1)
        umap[index] = x;
      actual += x - aux;
      std::cout << actual << '\n';
    }if(type_q == 2){
      std::cin >> todos;
      actual = todos*n;
      std::cout << actual << '\n';
      umap.clear(); //Limpiamos el mapa
    }
  }
    return 0;
  }
