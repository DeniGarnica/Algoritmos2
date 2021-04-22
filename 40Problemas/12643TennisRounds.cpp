#include <iostream>
using namespace std;
#include <math.h>

int main(){
  int n, a, b, r1, r2 ,res,aux, e;
  e=0;
  while(cin){
    if(e!=0)
      std::cout  << '\n';
  res=0;
  aux=1;
  e=1;
  std::cin >>n>>a>>b;
  while (aux) {
    if(a!=b&&a!=0&&b!=0){   //Seguimos avanzando de ronda hasta que les toque estar en el mismo bloque
      a=ceil((a+a%2)/2);
      b=ceil((b+b%2)/2);
      res++; //Si no estaban en el mismo bloque, paso una ronda mas
    }else{
      aux=0;
    }
  }
  std::cout << res;
  }
  return 0;
}
