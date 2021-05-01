#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int f(int a){
  //Hace algo y es la funcion que queremos encontrar su minimo
  return 0;
}

int min_funcion(int A, int B){ //Buscamos el min en el intervalo [A,B]
	while(B-A>0.0000001){
	int C= (2*A+B)/3;
	int D= (2*B+A)/3;
	if(f(C)==f(D)){
		B=D;
		A=C;
	}else{
		if(f(C)<f(D)){
			B=D;
		}else{
			A=C;
		}
	}
	}
	return(B); //Nos regresa el valor que minimiza la funcion
}

int main(){
  return 0 ;
}
