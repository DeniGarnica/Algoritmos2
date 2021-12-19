#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_casos;
  ll num, res;
  string numc;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> num;
    res = 0;
    while (num>9){
      res++;
      numc = to_string(num);
      num = 1;
      for (ll i = 0; i < numc.size(); i++) {
        num=num*((ll)numc[i] - 48);
        numc[i]='\0';
      }
      numc = to_string(num);
    }
    std::cout << res << '\n';
  }
    return 0;
  }
