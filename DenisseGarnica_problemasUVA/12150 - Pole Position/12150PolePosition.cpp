//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include <iostream>
using namespace std;

int main(){
int n=-1;
int c, p, aux1;
int aux2=0;
int respuesta;
do{
  aux2++;
  respuesta=1;
  std::cin >> n;
  int B[n][2];
  for (int i = 0; i < n; i++) {
    std::cin >> c >> p;
    aux1=i+p; //la forma de calcular la posicion inicial es su posicion actual + los lugares que subio
    if(aux1>=n||aux1<0){
      respuesta=-1; //si nos da una posaicion fuera del rango no hay acomodo posible
    }else{
      if(B[aux1][0]!=aux2){ //con esto reviso si alguien en este caso ya tuvo asignada la misma posicion inicial
        B[aux1][0]=aux2;
        B[aux1][1]=c;
      }else{
        respuesta=-1;
      }
    }
  }
  if(respuesta!=-1 && n!= 0){ // si hay una respuesta correcta imprimimos los casosas posi

    for (int i = 0; i < n; i++){
      std::cout << B[i][1];
      if(i<n-1){
        std::cout << " ";
      }
    }
    std::cout << '\n';
  }else{
    if(n!=0)
      std::cout <<"-1"<< '\n';
    }

  }while(n!=0);

    return 0;

}
