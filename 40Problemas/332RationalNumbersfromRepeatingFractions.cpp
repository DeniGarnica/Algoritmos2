#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

int gcd(int a, int b){
    if (a == 0)
        return b;
    return gcd(b % a, a);
}


void fraction(int k, int j, float x){
  int a = ceil(pow(10, k+j)*x - pow(10, k)*x);
  int b = pow(10, k+j)-pow(10, k);
  int d = gcd(a, b);
  a = int(a/d);
  b = int(b/d);
  std::cout << a<<"/"<<b << '\n';
}

int main(){
  int k, j, decimales, cont;
  float x;
  char aux;
  string aux2;
  char A[9];
  int caso = 1;
  std::cin >> j;
  while (j!=-1) {
    k=0; cont = 0;
    getchar(); getchar(); getchar();
    aux= getchar();
    while (aux!='\n') {
      A[cont]=aux;
      cont++;
      aux= getchar();
    }
    k=cont-j;
    A[cont]='\0';
    x=float(stoi(A))/pow(10,cont);
    cont=0;
    while (A[cont]==0) {
      x = x/10;
      cont++;
    }
    std::cout << "Case "<< caso <<": ";
    fraction(k, j, x);
    caso++;
    std::cin >> j;
  }
  return 0;
}
