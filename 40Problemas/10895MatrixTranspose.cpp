//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#include <queue>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int m, n, n_notzero, aux; //m = filas, n = columnas
  while(cin >> m >> n){
    int A[m][n];
    //Pre llenamos la matriz con ceros
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        A[i][j] = 0;

    for (int i = 0; i < m; i++) {
      std::cin >> n_notzero;
      int indice[n_notzero];
      for (int j = 0; j < n_notzero; j++)
        std::cin >> indice[j];
      for (int j = 0; j < n_notzero; j++)
        std::cin >> A[i][indice[j]-1]; //cambiamos los valores no ceros
    }

    std::cout << n<<" " << m<<'\n';
    int n_notzeros[n];
    queue<int> indice_T[n];
    queue<int> vals[n];

    for (int i = 0; i < n; i++) {
      n_notzeros[i] = 0;
      for (int j = 0; j < m; j++) {
        if(A[j][i] != 0){
          n_notzeros[i]++;
          indice_T[i].push(j);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      std::cout << n_notzeros[i]; //imprimos la cantidad de numeros no cero por columna
      if(n_notzeros[i]!=0)
        std::cout << " ";
      for (int j = 0; j < n_notzeros[i]; j++) {
        std::cout << indice_T[i].front()+1; //Imprimomos los indices de estos
        vals[i].push(A[indice_T[i].front()][i]);
        indice_T[i].pop();
        if(j<n_notzeros[i]-1)
          std::cout << " ";
      }
      std::cout  << '\n';
      for (int j = 0; j < n_notzeros[i]; j++){
        std::cout << vals[i].front(); //Y sus valores
        vals[i].pop();
        if(j<n_notzeros[i]-1)
          std::cout << " ";
      }
      std::cout  << '\n';
    }
  }
    return 0;
  }
