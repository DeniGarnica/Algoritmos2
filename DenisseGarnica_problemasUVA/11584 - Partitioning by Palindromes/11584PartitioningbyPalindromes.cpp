//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  bool palindrome[1010][1010];
  int partes[1010]; //partes[i] Nos dice la cantidad de particiones necesarias si el string fuera de tamanio i
  //palindrome[i][j] nos dice si del caracter i al j de el string s, es un palindromo
  int num_casos;
  string s;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    memset(palindrome,0,sizeof(palindrome));
    memset(partes,0,sizeof(partes));
    std::cin >> s;
    int len = s.size();
    for (int j = 0; j < len; j++){
      palindrome[j][j] = 1;
      if (j<len-1)
        if(s[j] == s[j+1]){ //Para los que tienen un caracter igual justo al lado
          palindrome[j+1][j] = 1;
          palindrome[j][j+1] = 1;
        }
    }
    for (int j = 3; j <= len; j++){//Calcula palindromos si el centro ya es palindromo
      for (int k = 0; k < len-j+1; k++){
        int l = j+k-1;
        if(s[k]==s[l]&&(palindrome[k+1][l-1])==1){
          palindrome[l][k] = 1;
          palindrome[k][l] = 1;
        }
      }
    }

    partes[0] = 1; //Si tenemos un solo caracter, solo es necesaria una particion
    for (int j = 1; j < len; j++) {
      if(palindrome[j][0]){ //Si del inicio al caracter j es un palindromo, entonces no se necesitan particiones
        partes[j]=1;
        continue;
      }
      partes[j] = 1010; //Le asignamos el maximo valor posible
      for (int k = 1; k < j; k++) //Ahora buscaremos si hay palindromos en el interior del string actual
        if(palindrome[j][k])
          partes[j] = min(partes[k-1]+1, partes[j]);
          //Si encontramos un palindromo contenido en el string,
          //vemos is la division al usar este palindromo es menor a la actual
      partes[j] = min(partes[j], partes[j-1]+1);
      //Ahora vemos si la division actual es mejor que la del string sin la ultima letra mas 1
    }
    std::cout << partes[len-1] << '\n';



  }
    return 0;
  }
