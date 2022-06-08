#include<bits/stdc++.h>
#define ll long long
#define MAX 100000
int resets[MAX];
int maxim[MAX];

//Esta funcion almacena los maximos de cada una de las columnas de
//los preprocess que inicia en cada indice
void kmpPreprocess_k(const std::string &p){
  for (int k = 0; k < p.size(); k++){
    int j = -1, i = k;
    resets[k] = -1;
    while(i < p.size()){
      while(j >= 0 && p[i] != p[j+k]) j = resets[k+j];
      i++; j++;
      resets[i] = j;
      if(resets[i] > maxim[i])
        maxim[i] = resets[i];
    }
    resets[k] = 0;

  }
}

//Le pasamos el tama;o de p y calcula la respuesta
int res(int n){
  int sum = 0;
  for (int i = 0; i <= n; i++)
    sum += (i - maxim[i]);
  return sum;
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
