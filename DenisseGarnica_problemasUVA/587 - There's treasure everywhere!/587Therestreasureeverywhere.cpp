//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long

//Comvierte la direccion a coordenadas
void to_number(std::string &s){
  double x = 0; double y = 0; double r = sqrt(2)/2;
  double num = 0; int n = s.size();
  for (int i = 0; i < n-1; i++) {
    if(s[i] >= '0' && s[i] <= '9'){
      num = num*10 + (s[i] - '0'); //vamos calculando el numero
      continue;
    }
    //vemos la direccion y le sumamos su valor correspondiente en la coordenada
    if(s[i] >= 'A' && s[i] <= 'Z'){
      if(s[i] == 'E' && (s[i+1] == ',' || s[i+1] == '.')){
        x += num;
        num = 0; i++;
        continue;
      }
      if(s[i] == 'N' && s[i+1] == 'E'){
        x += num*r;
        y += num*r;
        num = 0; i+=2;
        continue;
      }
      if(s[i] == 'N' && (s[i+1] == ',' || s[i+1] == '.')){
        y += num;
        num = 0; i++;
        continue;
      }
      if(s[i] == 'N' && s[i+1] == 'W'){
        x -= num*r;
        y += num*r;
        num = 0;  i+=2;
        continue;
      }
      if(s[i] == 'W' && (s[i+1] == ',' || s[i+1] == '.')){
        x -= num;
        num = 0; i++;
        continue;
      }
      if(s[i] == 'S' && s[i+1] == 'W'){
        x -= num*r;
        y -= num*r;
        num = 0; i+=2;
        continue;
      }
      if(s[i] == 'S' && (s[i+1] == ',' || s[i+1] == '.')){
        y -= num;
        num = 0; i++;
        continue;
      }
      if(s[i] == 'S' && s[i+1] == 'E'){
        x += num*r;
        y -= num*r;
        num = 0; i+=2;
        continue;
      }
    }

  }
  double dist = sqrt(x*x + y*y);
  printf("The treasure is located at (%.3lf,%.3lf).\n", x, y);
  printf("The distance to the treasure is %.3lf.\n\n", dist);
}

int main(){
  //std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string s;
  std::cin >> s;
  int cont = 1;
  while(s != "END"){
    std::cout << "Map #"<< cont << '\n';
    to_number(s);
    std::cin >> s;
    cont++;
  }
    return 0;
  }
