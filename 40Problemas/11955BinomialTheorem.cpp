#include <iostream>
#include <cmath>
using namespace std;
int F[51];
int factorial(int a){
  if(F[a]==0)
    F[a]= a*factorial(a-1);
  return F[a];
}

int C(int n, int k){
  return (int)(factorial(n)/(factorial(k)*factorial(n-k)));
}


void bin(char* A, char* B, int p){
  int aux;
  for (int i = 0; i <= p; i++) {
    aux = C(p, i);
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
