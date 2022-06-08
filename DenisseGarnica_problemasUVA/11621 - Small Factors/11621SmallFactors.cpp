//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long
std::vector<ll> v;

//preprocesamos las potencias
void potencias(){
    ll p;
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 32; j++) {
            p = pow(2, i) * pow(3, j);
            if(p > pow(2, 31)) break;
            v.push_back(p);
        }
    }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  ll N, res;
  potencias();
  std::sort(v.begin(), v.end()); //Las ordenamos
  while(std::cin>>N  && N != 0){
    //la funcion lower_bound nos regresa el iterador del primer elemento en el
    //rango que tiene un valor no menor que lo que ingresamos
    res = lower_bound(v.begin(), v.end(), N) - v.begin();
    std::cout << v[res] << '\n';
  }
    return 0;
  }
