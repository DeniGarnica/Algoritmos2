#include<bits/stdc++.h>
#define ll long long
#define MAX 100000
int resets[MAX];

void kmpPreprocess(const string &p){
  int i = 0, j = -1;
  resets[0] = -1;
  while(i < p.size()){
    while(j >= 0 && p[i] != p[j]) j = resets[j];
    i++; j++;
    resets[i] = j;
  }
}

int kmpMatch(const string &s, const string &p){
  int i = 0, j = 0, nc = 0;
  while(j >= 0 && s[i] != p[j]) j = resets[j];
  i++; j++;
  if(j == p.size()){
    nc++;
    j = resets[j];
  }
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos, dato1, dato2;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> dato1;
  }
    return 0;
  }
