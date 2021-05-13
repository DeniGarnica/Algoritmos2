#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

void fraction(int k, int j){
  
}

int main(){
  int k, j, decimales, cont;
  char aux;
  string aux2;
  char A[9];
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
    A[cont]='\0';
    std::cout << A << '\n';
    std::cin >> j;
  }
  return 0;
}
