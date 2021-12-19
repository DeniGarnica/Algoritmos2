#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_casos, cont, j, flag;
  string deck;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> deck;
    cont = 0;
    j = 0;
    flag = 0;
    while (j<deck.size()) {
      if(deck[j]=='B')
        cont++;
      if(deck[j]=='R')
        cont--;
      if(cont<0){
        flag = j+1;
        cont = 0;
      }
      j++;
    }
    std::cout << flag << '\n';
  }
    return 0;
  }
