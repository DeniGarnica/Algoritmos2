//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long
std::vector<std::pair<int, int>> v; //Guarda la suma de los divisores del segundo elemento
int Res[100010];

void pre_proces(){
  for (int i = 1; i <= 1000; i++) {
    int auxi = 1;
    for (int j = 1; j < i; j++){
      if(i % (j+1) == 0) //Calcula los divisores
        auxi += j+1; //Suma los divisores
    }
    Res[auxi] = i; //Guarda el mayor que de esa suma
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  memset(Res, -1, sizeof(Res));
  pre_proces();


  int N;
  std::cin>>N;
  int caso = 1;
  while(N != 0){
    std::cout <<"Case "<< caso <<": "<< Res[N] << '\n';
    caso++;
    std::cin>>N;
  }

    return 0;
  }
