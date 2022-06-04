#include<bits/stdc++.h>
#define ll long long

int distancia_H(std::string &a, std::string &b){
    int res = 0; int match = 0;
    for(int i = 0; i +  b.size() <= a.size(); i++){
        match = 0;
        for(int j = 0; j < b.size(); j++)
            if(a[i+j] == b[j]) match++; //vemos en cuantos caracteres coinciden
        if(res < match) res = match;
    }
    return res;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N, M;
  std::string aux;
  std::cin>>N >> M;
  std::vector<std::string> movies;
  for (int i = 0; i < N; i++){
    std::cin >> aux;
    movies.push_back(aux);
  }
  for (int i = 0; i < M; i++) {
    std::cin >> aux;
    int actual = 0;
    int mejor = 0;
    int res = 1;
    //vemos con cual de las cadenas coincide mas la que estamos viendo
    for (int j = 0; j < movies.size(); j++){
      actual = distancia_H(movies[j], aux);
      if(actual > mejor){
        mejor = actual;
        res = j+1;
      }
    }
    std::cout << res << '\n';
  }
    return 0;
  }
