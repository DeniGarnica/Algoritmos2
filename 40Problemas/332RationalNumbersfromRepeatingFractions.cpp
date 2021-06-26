#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

int gcd(int a, int b)
{
  int g;
    if (a == 0)
       return b;
    if (b == 0)
       return a;
    if (a == b)
        return a;
    if (a > b){
      while (a-b>b) {
        a=a-b;
      }
      g = gcd(a-b, b);
      return g;
    }
    while (b-a>a) {
      b=b-a;
    }
    g = gcd(a, b-a);
    return g;
}

void fraction(int k, int j, double x, double x2){
  std::cout << pow(10,k+j)*x+x2  << '\n';
  std::cout << pow(10,k)*x << '\n';
  int a = ceil(pow(10,k+j)*x+x2 - pow(10,k)*x);
  int b = ceil(pow(10, k)*(pow(10, j)-1));
  std::cout << "a: "<<a << '\n';
  //std::cout << "b: "<<b << '\n';
  int d = gcd(a, b);
  a = int(a/d);
  b = int(b/d);
  std::cout << a<<"/"<<b << '\n';
}

int main(){
  int k, j, decimales, cont;
  double x, x_2;
  char aux;
  string aux2;
  char A[9];
  char B[9];
  int caso = 1;
  std::cin >> j;
  while (j!=-1) {
    k=0; cont = 0;
    getchar(); getchar(); getchar();
    aux= getchar();
    while (aux>47&&aux<58) {
      A[cont]=aux;
      cont++;
      aux= getchar();
    }
    k=cont-j;
    int l=0;
    for (l = 0; l < j; l++) {
      B[l]=A[cont-j+l];
    }
    B[l]='\0'; A[cont]='\0';
    x=float(stoi(A))/pow(10,cont);
    x_2=float(stoi(B))/pow(10,j);
    cont=0;
    std::cout << "Case "<< caso <<": ";
    std::cout  << '\n';
    fraction(k, j, x, x_2);
    caso++;
    std::cin >> j;
  }
  return 0;
}
