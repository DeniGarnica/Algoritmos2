#include<bits/stdc++.h>
#define ll long long
#define MAX 50000
int resets[MAX];

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
  while(j >= 0 && s[i] != p[j]) j = resets[j];
  i++; j++;
  if(j == p.size()){
    nc++;
    j = resets[j];
  }
}

std::string diferencias(const std::string &s){ //Crea un string con las diferencias entre los caracteres
  std::string D, aux;
  for (int i = 0; i < s.size()-1; i++) {
    if(s[i]-s[i+1] < 0){
      aux = std::to_string(s[i]-s[i+1] + 26) + '.';
      D = D + aux;
    }else{
      aux = std::to_string(s[i]-s[i+1]) + '.';
      D = D + aux;
    }
  }
  return D;
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos;
  std::string p, s;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> p >> s;
    std::cout << diferencias(s) << std::endl;
  }
    return 0;
  }
