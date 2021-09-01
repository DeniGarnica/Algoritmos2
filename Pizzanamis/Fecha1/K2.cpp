#include<bits/stdc++.h>
using namespace std;

void rec(int k){
  if (k==0)
    return;
  if (k==1){
    std::cout << "2";
    return;
  }
  if(k==2){
    std::cout << "(2)^2";
    return;
  }
  if(k>1 && k%2==1){
    std::cout << "(2*";
    rec(k-1);
    std::cout << ")";
     return;
  }
  if(k>2 && k%2==0){
    std::cout << "(";
    rec(k/2);
    std::cout << ")^2";
     return;
  }
}

int main(){
  int t,k;
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    std::cin >> k;
    rec(k);
    std::cout << '\n';
  }
    return 0;
  }
