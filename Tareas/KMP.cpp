#include<bits/stdc++.h>
#define ll long long
#define MAX 100000
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
  while(i < s.size()){
    while(j >= 0 && s[i] != p[j]) j = resets[j];
    i++; j++;
    if(j == p.size()){
      nc++;
      j = resets[j];
    }
  }
  return nc;
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string s = "abcblabladeblablayblablablaxyz";
  std::string p = "blabla";
  kmpPreprocess(p);
  for (int i = 0; i < p.size(); i++){
    std::cout << resets[i] << " ";
  }
  std::cout  << std::endl;
  int k = kmpMatch(s, p);
  std::cout << kmpMatch(s, p) << std::endl;
    return 0;
  }
