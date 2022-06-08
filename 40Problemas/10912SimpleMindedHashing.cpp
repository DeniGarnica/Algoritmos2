//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long

int DP[30][30][400]; //Representa [letras consideradas][longitud][suma]

void forma_DP(){
  DP[0][0][0] = 1;
  for (int i = 1; i <= 26; i++)
    for (int j = 0; j <= i; j++)
      for (int k = 0; k <= 351; k++) {
        DP[i][j][k] = DP[i-1][j][k]; //Empieza siendo la misma longitud sin considerar la letra acyual
        if( j > 0 && k>= i) //Si al agregar la letra i-esima, el valor k no se pasa
          DP[i][j][k] += DP[i-1][j-1][k-i];
        //Agregamos la letra i-esima al final, por lo tanto solo necesitamos
        //de tama;o k-1 considerando las i-1-esimas letras
      }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  forma_DP();
  int L, S;
  int cont = 1;
  std::cin >> L >> S;
  while(L && S){
    if(L > 26 || S > 351)
      std::cout << "Case "<< cont << ": "<< 0 <<'\n';
    else
      std::cout << "Case "<< cont << ": "<< DP[26][L][S] <<'\n';
    cont++;
    std::cin >> L >> S;
  }

    return 0;
  }
