#include<bits/stdc++.h>
#define ll long long
int N;
int val[32790];
int potencias[32790];

int Sumas(){
  int res = 0;
  int actual = 0;
  int arista = 0;
  for (int j = 0; j < pow(2, N); j++){
    arista = potencias[j];
    for (int i = 0; i < N; i++){
      actual = pow(2, i);
      if(res < arista + potencias[(j^actual)])
        res = arista + potencias[(j^actual)];
    }
  }
  return res;
}

int Potencia_esquina(int n){
  int res = 0;
  int actual = 1;
  for (int i = 0; i < N; i++) {
    actual = pow(2, i);
    res+= val[(n^actual)]; //n^actual nos calcula los vecinos, pues las aristas difieren en un solo bit
  }
  potencias[n] = res;
  return res;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int actual;
  while(std::cin>>N){
    int n_aristas = pow(2, N);
    int res = 0;
    for (int i = 0; i < n_aristas; i++)
      std::cin >> val[i];
    for (int i = 0; i < n_aristas; i++){
      Potencia_esquina(i); //Calculamos las potencias de cada esquina
    }
    std::cout << Sumas() << std::endl;
  }
    return 0;
  }
