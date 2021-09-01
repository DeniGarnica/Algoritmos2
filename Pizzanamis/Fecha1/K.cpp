#include<bits/stdc++.h>
using namespace std;

void Divisores(string n){
  int flag = 0;
  int flag2=0;
  int flag3=0;
  int l;
  if(n.back()=='2'||n.back()=='4'||n.back()=='6'||n.back()=='8'||n.back()=='0'){
    std::cout << "2";
    flag=1;
    flag2=1;
  }
  if(n.size()<2){
    l = stoi(n);
  }else{
    l = stoi(n.substr( n.length() - 2 ));
  }
  int sum=0;
  for (int i = 0; i < n.size(); i++) {
    sum +=(n[i]-'0')%3;
  }
  if(sum%3==0){
    if(flag==0){
      std::cout << "3";
      flag=1;
      flag3=1;
    }else{
      std::cout << " 3";
      flag3=1;
    }
  }
  if(l%4==0){
    if(flag==0){
      std::cout << "4";
      flag=1;
    }else{
      std::cout << " 4";
    }
  }
  if(n.back()=='0'||n.back()=='5'){
    if(flag==0){
      std::cout << "5";
      flag=1;
    }else{
      std::cout << " 5";
    }
  }
  if(flag2&&flag3){
    if(flag==0){
      std::cout << "6";
      flag=1;
    }else{
      std::cout << " 6";
    }
  }
  if(flag==0){
    std::cout << "-1" << '\n';
  }else{
    std::cout << '\n';
  }
}

int main(){
  int n;
  std::cin >> n;
  string A[n];
  for (int i = 0; i < n; i++) {
    std::cin >> A[i];
    Divisores(A[i]);
  }

  return 0;
}
