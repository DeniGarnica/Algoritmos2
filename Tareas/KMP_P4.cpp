#include<bits/stdc++.h>
#define ll long long
#define MAX 100000
int resets_1[MAX];
int resets_p[MAX];
std::vector<int> v; //Almacenaremos los posibles shift que nos den el resultado

void kmpPreprocess_1(const std::string &p){
  int i = 0, j = -1;
  resets_1[0] = -1;
  while(i < p.size()){
    while(j >= 0 && p[i] != p[j]) j = resets_1[j];
    i++; j++;
    resets_1[i] = j;
  }
}

void kmpPreprocess_p(const std::string &p){
  int i = 0, j = -1;
  resets_p[0] = -1;
  while(i < p.size()){
    while(j >= 0 && p[i] != p[j]) j = resets_p[j];
    i++; j++;
    resets_p[i] = j;
  }
}

int kmpMatch_1(const std::string &s, const std::string &p, const std::string &s2, const std::string &p2){
  int i = 0, j = 0, nc = 0, dif = 0, cont = 0;
  while(i < s.size()){
    if(s[i] == '.')
      cont++;
    while(j >= 0 && s[i] != p[j]) j = resets_1[j];
    i++; j++;
    if(j == p.size()){
      dif = s2[cont] - p2[p2.size()-1];
      if(dif<0)
        dif = dif + 26;
      v.push_back(dif); //Almacena las posibles diferencias
      nc++;
      j = resets_1[j];
    }
  }
  return nc;
}

int kmpMatch_p(const std::string &s, const std::string &p){
  int i = 0, j = 0, nc = 0;
  while(i < s.size()){
    while(j >= 0 && s[i] != p[j]) j = resets_p[j];
    i++; j++;
    if(j == p.size()){
      nc++;
      j = resets_p[j];
    }
  }
  return nc;
}

//Crea un string con las diferencias entre los caracteres
std::string diferencias2(const std::string &s){
  std::string D, aux;
  for (int i = 0; i < s.size()-1; i++) {
    if(s[i]-s[i+1] < 0){ //Probablemente el timeout es por las concatenaciones
      aux = std::to_string(s[i]-s[i+1] + 26) + '.';
      D = D + aux;
    }else{
      aux = std::to_string(s[i]-s[i+1]) + '.';
      D = D + aux;
    }
  }
  return D;
}


//Crea un string con las diferencias entre los caracteres
std::string diferencias(const std::string &s){

  char D[3*s.size()];
  int actual = 0;
  for (int i = 0; i < s.size()-1; i++) {
    if(s[i]-s[i+1] < 0){ //Probablemente el timeout es por las concatenaciones
      if(s[i]-s[i+1] + 26 >=0 && s[i]-s[i+1] + 26 <= 9){
        D[actual] = s[i]-s[i+1] + 26 + '0';
        //std::cout << "D[actual] = "<<D[actual] << '\n';
        actual++;
        D[actual] = '.';
        actual++;
      }else{
        if(s[i]-s[i+1] + 26 >= 20 )
          D[actual] = '2';
        else
          D[actual] = '1';
        actual++;
        //std::cout << "D[actual] = "<<D[actual] << '\n';
        D[actual] = (s[i]-s[i+1] + 26)%10 + '0';
        //std::cout << "D[actual] = "<<D[actual] << '\n';
        actual++;
        D[actual] = '.';
        actual++;
      }
    }else{
      if(s[i]-s[i+1] >=0 && s[i]-s[i+1] <= 9){
        D[actual] = s[i]-s[i+1] + '0';
        //std::cout << "D[actual] = "<<D[actual] << '\n';
        actual++;
        D[actual] = '.';
        actual++;
      }else{
        if(s[i]-s[i+1]  >= 20 )
          D[actual] = '2';
        else
          D[actual] = '1';
        actual++;
        //std::cout << "D[actual] = "<<D[actual] << '\n';
        D[actual] = (s[i]-s[i+1])%10 + '0';
        //std::cout << "D[actual] = "<<D[actual] << '\n';
        actual++;
        D[actual] = '.';
        actual++;
      }
    }
  }
  D[actual] = '\0';
  return D;
}


//Realiza erl shift de una palabra
std::string shift(const std::string &s, int n){
  bool mayus = 1;
  int temp = 0;
  char new_s[s.size()];
  for (int i = 0; i < s.size(); i++) {
    if(s[i]>= 64 && s[i]<= 90){
      temp = s[i] - 'A' - n;
      mayus = 1;
    }else{
      temp = s[i] - 'a' - n;
      mayus = 0;
    }
    if(temp < 0){
      if(mayus)
        new_s[i] = 25 + temp + 'A' + 1;
      else
        new_s[i] = 25 + temp + 'a' + 1;
    }else{
      if(mayus)
        new_s[i] = temp + 'A';
      else
        new_s[i] = temp + 'a';
    }
  }
  new_s[s.size()] = '\0';
  return new_s;
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos;
  std::string p, s;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    //Para cada nuevo caso limpiamos la informacion
    v.clear();
    memset(resets_1, 0, sizeof resets_1);
    memset(resets_p, 0, sizeof resets_p);
    std::vector<int> res;

    //Ingresamos las nuevas cadenas
    std::cin >> p >> s;
    std::string D_s = diferencias(s);
    std::string D_p = diferencias(p);
    /*std::cout << "dif s" << '\n';
    std::cout << D_s << '\n';
    std::cout << "dif p" << '\n';
    std::cout << D_p << '\n';*/
    kmpPreprocess_1(D_p);
    kmpPreprocess_p(p);

    //Aqui calculara los posibles shifts que nos den resultados, los cuales estaran en v
    int k = kmpMatch_1(D_s, D_p, s, p);

    if(k>0){
      for (int j = 0; j < v.size(); j++) {
        //std::cout << "v[j] = "<< v[j] << '\n';
        //std::cout << shift(s, v[j]) << '\n';
        if(kmpMatch_p(shift(s, v[j]), p) == 1)
          res.push_back(v[j]);
      }
    }

    std::cout << res.size() <<" ";
    for (int k = 0; k < res.size(); k++)
      std::cout << res[k] << " ";
    std::cout << '\n';
  }
    return 0;
  }
