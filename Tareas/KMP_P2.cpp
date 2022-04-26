#include<bits/stdc++.h>
#define ll long long
#define MAX 100000
int resets[MAX];
int maxim[MAX];

/*
Idea
realizar el preproces de cada una de las subcadenas,
ie la que inicia en el indice 0, la que inicia en 1, ...

*/

void kmpPreprocess_k(const std::string &p){
  for (int k = 0; k < p.size(); k++){
    int j = -1, i = k;
    resets[k] = -1;
    while(i < p.size()){
      //std::cout << "j: "<< j<< "  i: "<< i;
      while(j >= 0 && p[i] != p[j+k]) j = resets[k+j];
      i++; j++;
      resets[i] = j;
      //std::cout << "    resets["<< i <<"] = "<< j << '\n';
      if(resets[i] > maxim[i])
        maxim[i] = resets[i];
    }
    resets[k] = 0;
    /*std::cout << "resets actuales" << '\n';
    for (int k = 0; k <= p.size(); k++)
        std::cout << resets[k] << " ";
    std::cout  << '\n';*/
  }
}

//Le pasamos el tama;o de p
int res(int n){
  int sum = 0;
  for (int i = 0; i <= n; i++)
    sum += (i - maxim[i]);
  return sum;
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
  kmpPreprocess_k(p);
  std::cout << res(p.size())<< '\n';
    return 0;
  }
