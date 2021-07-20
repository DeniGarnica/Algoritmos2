#include <iostream>
#include <cmath>
using namespace std;

int main(){
int T, num_dots, min_x, max_x;
float eje;
std::cin >> T;

while (T--) {
  std::cin >> num_dots;
  int A[num_dots][2];
  int dist = 0;
  for (size_t i = 0; i < num_dots; i++) {
    std::cin >> A[i][0];
    std::cin >> A[i][1];
    if(i==0||A[i][0]<min_x)
      min_x = A[i][0];
    if(i==0||A[i][0]>max_x)
      max_x = A[i][0];
  }
  if(num_dots==1){
    std::cout << "YES" << '\n';
  }else{
    eje = (float)(min_x + max_x)/2; //Aqui debe esatr el eje de simetria
    for (size_t j = 0; j < num_dots; j++)
      dist += A[j][0];
    if ((float)dist == eje*num_dots) //para que exista simetria el promedio de las distnacias al eje debe ser el eje mismo
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}

    return 0;
  }
