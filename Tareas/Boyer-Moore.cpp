#include<bits/stdc++.h>
#define ll long long
#define MAX 1000000
//En esta implementacion se uso el alfabeto completo usual,
//por lo que para cambiar esto se deben hacer algunos cambios
//como el tama;o de las siguientes dos constantes
#define ALP_SIZE 26 //Nos dice el tama;o del alfabeto
#define INI 97 //Este es el inicio en la tabla ascii
int resets[MAX];
int resets_rev[MAX];
int gs[MAX]; //good suffix
int bc[ALP_SIZE]; //bad char

//kmp de la cadena normal
void kmpPreprocess(const std::string &p){
  int i = 0, j = -1;
  resets[0] = -1;
  while(i < p.size()){
    while(j >= 0 && p[i] != p[j]) j = resets[j];
    i++; j++;
    resets[i] = j;
  }
}

//kmp de la reversa
void kmpPreprocess_rev(const std::string &p){
  int i = 0, j = -1;
  resets_rev[0] = -1;
  while(i < p.size()){
    while(j >= 0 && p[i] != p[j]) j = resets_rev[j];
    i++; j++;
    resets_rev[i] = j;
  }
}

//preprocesa el buen sufijo
void goodSuffixShift(std::string p){
  auto m = p.size();

  //Funcion de prefijos para p
  kmpPreprocess(p);

  //Funcion de prefijos para el reverso de p
  reverse(p.begin(), p.end());
  kmpPreprocess_rev(p);

  //Si gs no esta antes que la posicion actual
  //deducimos el shift con el mayor sufijo-prefijo
  for (int j = 0; j < m; j++)
    gs[j] = m - 1 - resets[m-1];
  gs[m - 1] = 1;

  //Determina sufijos iguales a las subcadenas previas
  for (int l = 1; l <= m; l++) {
    int j = m-1 - resets_rev[l];
    if(gs[j] > l - resets_rev[l])
      gs[j] = l - resets_rev[l];
  }
}

//preprocesa el caracter malo
void badCharShift(std::string &s){
    //Inicializamos en -1
    for(int i = 0; i < ALP_SIZE; i++)
        bc[i] = -1;

    //Ponemos la ultima aparicion de cada caracter
    for(int i = 0; i < s.size(); i++)
        bc[((int) s[i]) - INI] = i;
}

//Usa los preprocesamnientos para hacer las comparaciones
int BoyerMoore(const std::string &s, const std::string &p){
  int n = s.size();
  int m = p.size();

  int shift = 0;
  int cont = 0;
  while(shift < n - m){
    int j = m - 1;
    //escaneamos de derecha a izquierda
    while (j>=0 && p[j] == s[shift+j])
      j--;
    if(j < 0){
      shift += gs[0];
      cont++;
    }else
      shift += std::max(gs[j], j-bc[((int) s[shift+j]) - INI]);
  }
  return cont;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string p, s;
  std::cin >> p >> s;
  badCharShift(p);
  goodSuffixShift(p);
  std::cout << BoyerMoore(s, p) << '\n';
    return 0;
  }
