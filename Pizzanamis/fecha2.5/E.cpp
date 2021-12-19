#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long tam, x , y;
  string s;
  long long res;
  while(cin){
    cin >> s >> tam;
    for (long long i=0 ; i < tam ; i++){
      cin >> x >> y;
      x--;
      y--;
      res = (x+y)%tam;
      std::cout << s[res] << '\n';
    }
    }
    return 0;
}
