#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int n=0;
  int cont=0;
  std::cin >> n;
  float largo, ancho, prof, peso, total;
  for(int i=0;i<n;i++){
    std::cin >> largo;
    total=largo;
    std::cin >> ancho;
    total+=ancho;
    std::cin >> prof;
    total+=prof;
    std::cin >> peso;
    if(peso>7){
      std::cout << "0" << '\n';
    }else{
      if(largo>56 || ancho>45 || prof>25){ //si alguna medida se pasa
        if(total<=125){ //checamos la otra condicion
          std::cout << "1" << '\n';
          cont++;
        }else{
          std::cout << "0" << '\n';
        }
      }else{
        std::cout << "1" << '\n';
        cont++;
      }
    }
  }
  std::cout << cont << '\n';
  return 0;
}
