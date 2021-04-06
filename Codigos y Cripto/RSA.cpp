#include <iostream>
#include <cmath>
using namespace std;

int mcd(int a, int b){
    int aux;
    while (1){
        aux = a%b;
        if (aux == 0)
          return b;
        a = b;
        b = aux;
    }
}

int main(){
double p=5; //primo1 llave
double q=11; ////primo2 llave
double N=p*q; //Esta es la parte 1 de nuestra llave publica
double phi=(p-1)*(q-1); //Lave privada
double c=2;
double n2, c2; //Llaves publicas de otra persona
while (c < phi){ //De esta forma nos aseguramos que (phi,c)=1 y menor a f
        if (mcd(c, phi)==1)
            break;
        else
            c++;
}
std::cout << "Laves publicas: "<<N<<" "<<c<< '\n';
//Para este momento c es la parte 2 de la llave publica
//Ahora calculemos la llave privada, la cual es d tal que ed = 1 mod (p-1) (q-1)
int k= 2; // una constante cualquiera
double aux= fmod((1+(phi*k)),c);
double d = ((1+(phi*k))-aux)/c; //Recordemos que c y d son inversos

double mensaje, encriptado;

std::cout << "1. Si desea encriptar el mensaje con la llave publica de alguine mas" << '\n';
std::cout << "2. Si desea encriptar el mensaje con sus llaves privadas" << '\n';
std::cout << "3. Si desea desencriptar el mensaje con las llaves publicas de alguien mas" << '\n';
std::cout << "4. Si desea desencriptar el mensaje con sus llaves privadas" << '\n';
int action=0;
std::cin >> action;

if(action ==1){
  std::cout << "Ingrese mensaje a encriptar" << '\n';
  std::cin >> mensaje;
  std::cout << "Ingrese llaves publicas" << '\n';
  std::cin >> n2 >> c2;
  encriptado = pow(mensaje, c2);
  encriptado = fmod(encriptado,n2);
  std::cout << "El mensaje encriptado es "<< encriptado << '\n';
}
if(action ==2){
  std::cout << "Ingrese mensaje a encriptar con sus llaves privadas" << '\n';
  std::cin >> mensaje;
  encriptado = pow(mensaje, d);
  encriptado = fmod(encriptado,N);
  std::cout << "El mensaje encriptado es "<< encriptado << '\n';
}
if(action ==3){
  std::cout << "Ingrese mensaje a desencriptar" << '\n';
  std::cin >> encriptado;
  std::cout << "Ingrese llaves publicas" << '\n';
  std::cin >> n2 >> c2;
  mensaje = pow(encriptado, c2);
  mensaje= fmod(mensaje,n2);
  std::cout << "El mensaje desencriptado es "<< mensaje << '\n';
}

if(action ==4){
  std::cout << "Ingrese mensaje a desencriptar con sus llaves privadas" << '\n';
  std::cin >> encriptado;
  mensaje = pow(encriptado, d);
  std::cout << mensaje << '\n';
  mensaje= fmod(mensaje, N);
  std::cout << "El mensaje desencriptado es "<< mensaje << '\n';
}

  return 0;
}
