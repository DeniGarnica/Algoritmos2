#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;


int main(){
int largo,ancho, q, L, U, maxSize;
std::cin >> largo;
std::cin >> ancho;
while (largo != 0 && ancho != 0){
  int A[largo][ancho];
  for (size_t i = 0; i < largo; i++) {
    for (size_t j = 0; j < ancho; j++) {
      std::cin >> A[i][j];
    }
  }
  std::cin >> q;
  for (size_t i = 0; i < q; i++) {
  std::cin >> L>> U;
  maxSize = 0;
  for(int i = 0; i < largo; ++i){
				int minPosition = lower_bound(A[i], A[i] + ancho, L) - A[i]; //Nos dice en que posicion del arreglo esta el numero minimo, mayor igual a nuestra cota
				for(int j = maxSize; j < largo; ++j){
					if(largo <= i + j || ancho <= minPosition + j || U < A[i + j][minPosition + j])
						break; //Primero checamos si se pasa de largo y ancho del arreglo al extender un poco mas, si no se pasa, vemos si el numero en la esquina inferior derecha esta dentro de la cota
                  //En caso de estar en la cota vemos si el area es mayor a la que ya tenemos
				  maxSize = max(maxSize, j + 1);
				}
			}
      std::cout << maxSize << '\n';
  }
  std::cout << "-" << '\n';
  std::cin >> largo;
  std::cin >> ancho;
}

 return 0;
}
