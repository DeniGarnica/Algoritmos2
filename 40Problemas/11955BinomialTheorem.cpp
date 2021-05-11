#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int F[51];
int C[51][51];
int factorial(int a){
  if(F[a]==0)
    F[a]= a*factorial(a-1);
  return F[a];
}


int Combi(int n){
  C[n][0]=1; C[n][n]=1;
  if(n>0){
    C[n][1]=n; C[n][n-1]=n;
  }
  if(n>4){
  if (C[n-1][0]==1) {
    for (int k = 2; k < n-2; k++){
      C[n][k]= C[n-1][k-1] + C[n-1][k];
    }
  }else{
    for (int k = 2; k < n-2; k++){
      C[n][k]= (int)(factorial(n)/(factorial(k)*factorial(n-k)));
    }
  }
  }
}

int Com(int n, int k){
  if (C[n][0]!=1) {
    Combi(n);
  }
  return C[n][k];
}


void bin(char* A, char* B, int p){
  int aux;
  for (int i = 0; i <= p; i++) {
    aux = Com(p, i);
    if (aux!=1)
      std::cout << aux<<"*";
    if (i!=p) {
      std::cout <<A;
      if (p-i!=1)
        std::cout << "^"<<p-i;
      if(i!=0){
        std::cout << "*";
      }else{
        std::cout << "+";
      }
    }
    if (i!=0) {
      std::cout <<B;
      if (i!=1)
        std::cout << "^"<<i;
      if(i!=p)
        std::cout << "+";
    }
  }
}

int main(){
  for (int i = 0; i < 50; i++) {
    F[i]=0;
  }
  F[0]=1;
  F[1]=1;

  int n;
  string op;
  char A[50];
  char B[50];
  int cont = 0;
  char aux;
  int p;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> aux;
    std::cin >> aux;
    while (aux!='+') {
      A[cont]=aux;
      cont++;
      std::cin >> aux;
    }
    A[cont]='\0';
    cont=0;
    std::cin >> aux;
    while (aux!=')') {
      B[cont]=aux;
      cont++;
      std::cin >> aux;
    }
    B[cont]='\0';
    std::cin >> aux;
    std::cin >> p;

    std::cout << "Case "<< i+1 <<": ";
    bin(A, B, p);
    if(i!=n-1)
      std::cout  << '\n';
    cont=0;

  }

  return 0;
}
