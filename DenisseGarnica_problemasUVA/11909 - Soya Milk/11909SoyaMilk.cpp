//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main(){
int num_cases;
const double PI  = acos(-1.0);
double angulo, largo, ancho, alto;
double respuesta, angulo_rad;
while (scanf("%lf%lf%lf%lf", &largo, &ancho, &alto, &angulo) != EOF) {
  angulo_rad = (angulo*PI)/180.0; //Convertimos el angulo a radianes
  double h = tan(angulo_rad)*largo; // esta es la altura del triangulo recto que se genera del vacio
		if (h <= alto) { //Si la altura de este triangulo no es mayor a la altura de esta caja
			respuesta = largo * (alto - h /2.0) * ancho; //Se le resta el triangulo al volumen total
		}else{ //En el otro caso se calcula el triangulo de la leche que queda
        printf("h: %lf\n", h);
			angulo = 90 - angulo;
      angulo_rad = (angulo*PI)/180.0;
			respuesta = (alto* tan(angulo_rad) * alto / 2.0) * ancho;
		}
  printf("%.3lf mL\n", respuesta);
}
return 0;}
