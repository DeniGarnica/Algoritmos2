//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include <iostream>
#include <cmath>
using namespace std;

//Hacemos un switch que traduzca de arabigo a Braile
void braile(char a, string* A){
  switch(a) {
    case '1':
      A[0]="*.";
      A[1]="..";
      A[2]="..";
      break;
    case '2':
      A[0]="*.";
      A[1]="*.";
      A[2]="..";
      break;
    case '3':
      A[0]="**";
      A[1]="..";
      A[2]="..";
      break;
    case '4':
      A[0]="**";
      A[1]=".*";
      A[2]="..";
      break;
    case '5':
      A[0]="*.";
      A[1]=".*";
      A[2]="..";
      break;
    case '6':
      A[0]="**";
      A[1]="*.";
      A[2]="..";
      break;
    case '7':
      A[0]="**";
      A[1]="**";
      A[2]="..";
      break;
    case '8':
      A[0]="*.";
      A[1]="**";
      A[2]="..";
      break;
    case '9':
      A[0]=".*";
      A[1]="*.";
      A[2]="..";
      break;
    case '0':
      A[0]=".*";
      A[1]="**";
      A[2]="..";
      break;
}
}

//Hacemos una funcion que reciba el braile y traduzca a arabigo
int arabigo(string* A){
  if(A[0]=="*."&&A[1]=="..")
    return 1;
  if(A[0]=="*."&&A[1]=="*.")
    return 2;
  if(A[0]=="**"&&A[1]=="..")
    return 3;
  if(A[0]=="**"&&A[1]==".*")
    return 4;
  if(A[0]=="*."&&A[1]==".*")
    return 5;
  if(A[0]=="**"&&A[1]=="*.")
    return 6;
  if(A[0]=="**"&&A[1]=="**")
    return 7;
  if(A[0]=="*."&&A[1]=="**")
    return 8;
  if(A[0]==".*"&&A[1]=="*.")
    return 9;
  if(A[0]==".*"&&A[1]=="**")
    return 0;
}

int main() {
  int D=-1;
  char L;
  while (D!=0) {
    std::cin >> D;
  if(D!=0){
    std::cin >> L;
    if (L == 'S') {
      getchar();
      char A[D];
      string B[D][3];
      for (int i = 0; i < D; i++) {
        A[i]=getchar();
        braile(A[i], B[i]);
      }

      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < D; j++) {
          std::cout << B[j][i];
          if (j<D-1)
            std::cout << " ";
        }
        std::cout  << '\n';
      }

    } else {
      char A[D];
      string B[D][3];
      string aux;
      int aux2;
      for (int k = 0; k < 3; k++) {
      for (int i = 0; i < D; i++) {
        std::cin >> aux;
        B[i][k]=aux;
      }}
      for (int i = 0; i < D; i++) {
        aux2 = arabigo(B[i]);
        std::cout << aux2;
      }
      std::cout << '\n';


    }}
  }
  return 0;
}
