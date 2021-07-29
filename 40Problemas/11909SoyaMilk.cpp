#include<bits/stdc++.h>
#include<math.h>
using namespace std;

int main(){
int num_cases;
double angulo, largo, ancho, alto;
double respuesta;
std::cin >> num_cases;
while (num_cases--) {
  std::cin >> largo >>ancho>>alto>>angulo;
  angulo =angulo*3.14159265/180;
  respuesta = ancho*largo*(alto - (largo*sin(angulo)*cos(angulo))/2);
  std::cout << respuesta <<" mL" << '\n';
}


return 0;}
