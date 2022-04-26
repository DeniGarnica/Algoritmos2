#include<bits/stdc++.h>
#define ll long long
#define MAX 100000
int resets[MAX];

/*
Idea
Realizamos el preproces de la cadena, el ultimo valor en resets nos dara
en donde esta su prefijo mas grande, que a su vez nos da el siguiente prefijo
mas grande que es sufijo.
Despues solo nos es necesario buscar la cantidad de veces que aprecen cada uno
de estos prefijos en la cadena entera e imprimirlos.
*/


void kmpPreprocess(const std::string &p){
  int i = 0, j = -1;
  resets[0] = -1;
  while(i < p.size()){
    while(j >= 0 && p[i] != p[j]) j = resets[j];
    i++; j++;
    resets[i] = j;
  }
}

int kmpMatch(const std::string &s, const std::string &p){
  int i = 0, j = 0, nc = 0;
  while(i < s.size()){
    while(j >= 0 && s[i] != p[j]) j = resets[j];
    i++; j++;
    if(j == p.size()){
      nc++;
      j = resets[j];
    }
  }
  return nc;
}

//Busca la cantidad de veces que aparece un caracter en una cadena
int charMatch(const std::string &s, const char p){
  int nc = 0;
  for (int i = 0; i < s.size(); i++) {
    if(s[i] == p)
      nc++;
  }
  return nc;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string p;
  std::cin >> p;
  int actual = -2;
  kmpPreprocess(p);

  //Aqui se almacenan las posiciones de los prefijos que nos interesan
  std::vector<int> res_pos;
  //Tomamos el ultimo valor de los resets para que nos dijga la pos del prefijo
  actual = resets[p.size()];

  //Mientras no nos diga que no hay prefijo, seguimos buscando
  while(actual > 0 ){
      res_pos.push_back(actual);
      actual = resets[actual];
  }

  //En esta cadena iremos almacenando la subcadena prefijo sufijo
  char s[p.size()+1];

  int res, actual_1 = 0;
  //Por cada uno de los sufijos-prefijos
  for (int i = 0; i < res_pos.size(); i++){
      //Ya que estan guardados al reves
      actual = res_pos[res_pos.size() - 1 - i];
      for (int k = actual_1; k < actual ; k++){
        if(k<p.size()&& k>=0)
          s[k] = p[k]; //Copiamos lo que falta de la cadena
      }
      actual_1 = actual; //Esto es para no copiar dos veces
      s[actual] = '\0'; //Ponemos el final de la cadena

      memset(resets, 0, sizeof resets); //Reiniciamos los resets
      kmpPreprocess(s); //Realizmos el preproces de la cadena que vamos a buscar
      res = kmpMatch(p, s); //Buscamos la cantidad
      std::cout << s << " " << res << '\n'; //imprimimos resultado
  }
  std::cout << p << " 1" << '\n'; //sabemos que este caso siempre se cumplira al final
    return 0;
  }
