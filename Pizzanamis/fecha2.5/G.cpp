#include<bits/stdc++.h>
using namespace std;
#define ll long long

void intToBinario(int n){
    int bin[8];
    for (int i = 0; i < 8; i++) {
      bin[i] = 0;
    }
    int i = 0;
    while (n > 0) {
        bin[7-i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = 0; j < 8; j++) {
      std::cout << bin[j];
    }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string ip, sub, sub2, sub3, sub4;
  int a;
  std::cin >> ip;
  int i = 0;
  while(ip[i]!='.'){
    sub += ip[i];
    i++;
  }
  i++;
  a = stoi(sub);
  intToBinario(a);

  while(ip[i]!='.'){
    sub2 += ip[i];
    i++;
  }
  i++;
  a = stoi(sub2);
  intToBinario(a);

  while(ip[i]!='.'){
    sub3 += ip[i];
    i++;
  }
  i++;
  a =stoi(sub3);
  intToBinario(a);

  while(i<ip.size()){
    sub4 += ip[i];
    i++;
  }
  a =stoi(sub4);
  intToBinario(a);
  std::cout  << '\n';
    return 0;
  }
