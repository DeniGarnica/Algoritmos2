//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string s;
  int a, b, c;
  int res = 0;
  while(std::cin>>s){
    int i = 0; a = 0; b = 0; c = 0;
    for (i = 0; i < s.size(); i++){
      //seguimos agregando al primer valor hasta que llegue el primer signo
      if(s[i] == '+' || s[i] == '-') break;
      a *= 10; //si tiene un digito mas
      a += (s[i] - '0'); //le sumamos la actual unidad
    }
    char signo = s[i]; i++;
    for (i; i < s.size(); i++){
      //seguimos agregando al segundo valor hasta llegar al signo igual
      if(s[i] == '=') break;
      b*=10;
      b += (s[i]-'0');
    }
    i++;
    for (i; i < s.size(); i++){
      //seguimo agregando hasta llegar al final o ver un signo de interrogacion
      if(s[i] == '?' || s[i] == '\0') break;
      c*=10;
      c += (s[i]-'0');
    }

    if(signo == '+')
        if(a + b == c) res++;
    if(signo == '-')
        if(a -b == c) res++;
  }
  std::cout << res << '\n';
    return 0;
  }
