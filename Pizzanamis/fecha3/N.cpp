#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ll num_comp, participantes;
  std::cin >> num_comp >> participantes;
  ll A[num_comp]; //num de ganadores de cada anio
  for (ll i = 0; i < num_comp; i++) {
    std::cin >> A[i];
  }
  //retiro= indice del primer anio que no prticiparon
  //seguimiento = anios que siguieron viendo
  ll lugar[participantes], retiro[participantes], seguimiento[participantes];
  ll resentimiento[participantes];
  std::vector<ll> posibles;
  ll min = num_comp;
  ll max = 0;
  for (ll i = 0; i < participantes; i++) {
    std::cin>> retiro[i] >> lugar[i]>>seguimiento[i];
    seguimiento[i]--;
    resentimiento[i] = 0;
    if(lugar[i]>A[retiro[i]-1]){
      posibles.push_back(i);
      if(retiro[i]<min)
        min = retiro[i];
      if(retiro[i] + seguimiento[i] >max)
        max = retiro[i] + seguimiento[i];
    }
  }
  ll actual, retir;
  if(posibles.size()>0){
    //std::cout << "max "<< max << '\n';
    //std::cout << "min "<< min << '\n';
  for (ll k = 0; k < max-min+1; k++) {
    actual = A[min+k];
    for (ll i = 0; i < posibles.size(); i++) {
      retir = retiro[posibles[i]];
      //std::cout  << '\n';
      //std::cout << "persona "<< posibles[i] << '\n';
      //std::cout << "anio a ver "<< min+k << '\n';
      //std::cout << "dejo de participar "<< retir << '\n';
      //std::cout << "ultimo anio que vio "<< retir + seguimiento[i]<< '\n';
      if(min+k>= retir && retir + seguimiento[i] >= min+k){
        //std::cout << "se vio" << '\n';
        if(actual>=lugar[posibles[i]]){
          resentimiento[posibles[i]]++;
          //std::cout << "le dolio" << '\n';
        }
      }
    }
  }
  }

  for (ll i = 0; i < participantes; i++) {
    std::cout << resentimiento[i] << '\n';
  }
    return 0;
  }
