#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_casos, tam;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> tam;
    char A[tam][tam];
    for (int j = 0; j < tam; j++) {
      for (int k = 0; k < tam; k++)
        std::cin >> A[j][k]; //Ingresa los datos del cuadrado
    }

    for (int j = 0; j < tam; j++) {
      for (int k = 0; k < tam; k++){
        if(A[j][k]=='.'){
          for (char c = 'A'; c <= 'Z'; c++) { //Lo llena con la primer letra no usada por ningun vecino
            if(j-1>=0 && A[j-1][k] == c)continue;
            if(j+1<tam &&A[j+1][k] == c)continue;
            if(k-1>=0 &&A[j][k-1] == c)continue;
            if(k+1<tam &&A[j][k+1] == c)continue;
            A[j][k] = c;
            break;
          }
        }
      }
    }
    std::cout << "Case "<<i+1<<":" << '\n';
    for (int j = 0; j < tam; j++) {
      for (int k = 0; k < tam; k++)
        std::cout << A[j][k];
      std::cout  << '\n';
    }

  }
    return 0;
  }
