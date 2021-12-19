#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tiempo, vuelo, comidas, aux, aux1, aux2;
  std::cin >> tiempo >> vuelo >> comidas;
  int C[comidas+2];
  aux1 = 0;
  aux2 = 0;
  if(comidas==0){
    if(vuelo>=tiempo){
      std::cout << "Y" << '\n';
    }else{
      std::cout << "N" << '\n';
    }
    return 0;
  }

  for (int i = 0; i < comidas; i++) {
    std::cin >> aux;
    aux2 = aux - aux1;
    if(aux2 >= tiempo){
      std::cout << "Y" << '\n';
      return 0;
    }
    aux1 = aux;
  }
    aux2 = vuelo - aux;
    if(aux2 >= tiempo){
      std::cout << "Y" << '\n';
      return 0;
    }
    std::cout << "N" << '\n';
    return 0;
  }
