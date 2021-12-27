#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_casos, n, p, r;
  /* cola[i][j][k] representa la cola de
    i personas donde
    j se ven desde la derecha y
    k desde la izquierda */
  ll cola[15][15][15];
  memset(cola, 0, sizeof(cola)); //Empezamos llenando los datos de ceros
  cola[1][1][1] = 1; //Creamos el caso base, que es de una persona

  for (int i = 2; i < 14; i++)
    for (int j = 1; j < i; j++)
      for (int k = 1; k < i; k++)
        cola[i][j][k] = cola[i-1][j-1][k] + cola[i-1][j][k-1] + cola[i-1][j][k]*(i-2)
  /*
  Notemos que podemos dividir la cola en 3 casos,
  los cuales dependen de donde se encuentra la persona mas bajita de la cola
  Si esta persona esta hasta delante, 
  */
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> n >> p >>r;
    std::cout << cola[n][p][r] << '\n';
  }
    return 0;
  }
