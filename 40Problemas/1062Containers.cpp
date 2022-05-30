#include<bits/stdc++.h>
#define ll long long
/*
Podemos rehusar una pila si el elemento nuevo es el mismo que esta hasta arriba
o si el elemento nuevo se va a recoger antes del que esta ahora hasta arriba
iremos viendo cuantas pilas nuevas son necesarias crear checando esto
 */

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string s;
  std::cin >> s;
  int i = 1;
  while( s != "end"){
    std::vector<std::stack<char>> v; //Almacenaremos las pilas que hagamos
    std::stack<char> actual;

    //Empezamos agregando la primer letra a nuestra primer pila
    actual.push(s[0]);
    v.push_back(actual);
    actual.pop();
    bool nuevo; //Nos indica si es necesario crear una nueva pila
    for (int j = 1; j < s.size(); j++) {
      nuevo = 1;
      //Vamos checando si podemos meterlo a alguna de las pilas actuales
      for (int k = 0; k < v.size(); k++){
        //Si lo que esta hasta arriba de la pila que estamos checando va en el
        // mismo barco o en uno anterior,
        if(s[j]<=v[k].top()){
          v[k].push(s[j]);//lo metemos a esa pila
          nuevo = 0; //indicamos que no es necesario crear una nueva pila
          break; //dejamos de buscar
        }
      }
      if(nuevo){ //Si ninguna de las pilas no nos sirve, creamos una nueva
        actual.push(s[j]);
        v.push_back(actual);
        actual.pop();
      }
    }
    std::cout << "Case "<<i<<": "<< v.size() << '\n';
    std::cin >> s;
    i++;
  }
    return 0;
  }
