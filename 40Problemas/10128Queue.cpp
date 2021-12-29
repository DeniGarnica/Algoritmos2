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
   //Empezamos llenando los datos de ceros
  for (int i = 0; i < 15; i++)
    for (int j = 0; j < 15; j++)
      for (int k = 0; k < 15; k++)
        cola[i][j][k] = 0;
  cola[1][1][1] = 1; //Creamos el caso base, que es de una persona

  for (int i = 2; i < 14; i++)
    for (int j = 1; j <= i; j++)
      for (int k = 1; k <= i; k++)
        cola[i][j][k] = cola[i-1][j-1][k] + cola[i-1][j][k-1] + cola[i-1][j][k]*(i-2);
  /*
  Notemos que podemos dividir la cola en 3 casos,
  los cuales dependen de donde se encuentra la persona mas bajita de la cola
  Sea una cola[i][j][k]
  Si esta persona esta hasta delante, entonces si la quitamos tenemos una cola de i-1 personas,
  donde se ven ahora solo j-1 desde la izquierda, y como no se veia desde la derecha, este numero se mantiene
  Analogamente si esta persona esta atras, al quitarla tenemos una cola[i-1][j][k-1],
  pues se redujo una persona, no se veia desde la izquierda por lo que es la misma cantidad,
  y se ve una persona menos desde la derecha.
  En caso de no estar en los extremos esta persona no se ve. Por lo que puede estar en (i-2) posibles lugares en medio
  */
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> n >> p >>r;
    std::cout << cola[n][p][r] << '\n';
  }
    return 0;
  }
