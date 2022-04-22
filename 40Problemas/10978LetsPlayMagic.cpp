#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_cards;
  std::cin >> num_cards;
  while(num_cards){
    int disponibles = num_cards;
    string Orden[num_cards]; //En que orden estaban las cartas
    int Marcadas[num_cards]; //Marcamos cuando la casilla esta ocupada
    string Cards_n[num_cards]; //nombre de la carta
    string aux;
    int aux2, avanza, Card_L; //tamano del string
    int actual = 0;
    int posicion = actual;
    for (int i = 0; i < num_cards; i++) //Ponemos a todas las cartas sin marcar
      Marcadas[i] = 0;
    for (int i = 0; i < num_cards; i++){
      std::cin >> Cards_n[i];
      std::cin >> aux;
      Card_L = aux.size(); //Solo nos es necesario guardar el tamano de la carta
      if(Card_L != (disponibles)){
        avanza = Card_L%(disponibles);
      }else{
        avanza = disponibles;
      }
      //std::cout << "avanza: " << avanza << std::endl;
      aux2 = actual + avanza;
      int avanzados = actual;
      if(avanza == 0){
        while(Marcadas[actual-1] == 1){
          if(actual >= num_cards)
            actual = actual%num_cards;
          actual++;
        }
      }else{
        while(avanzados < aux2){
          if(actual >= num_cards)
            actual = actual%num_cards;
          if(Marcadas[actual] != 1){
            avanzados++;
            //std::cout << "estaba vacio "<< actual << std::endl;
          }
          actual++;
        }
      }
      int auxi;
      auxi = actual-1;
      if(auxi < 0)
        auxi = 0;
      //std::cout << "auxi = "<< auxi << '\n';

      Orden[auxi] = Cards_n[i];
      //std::cout << "Orden["<< auxi <<"]: " << Orden[auxi] << std::endl;
      Marcadas[auxi] = 1;
      disponibles--;
    }
    for (int i = 0; i < num_cards; i++){
      std::cout << Orden[i] << " ";
    }
    std::cout  << '\n';
    std::cin >> num_cards;
  }
    return 0;
  }
