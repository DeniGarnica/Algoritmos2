#include<bits/stdc++.h>
#define ll long long
ll arr[1000001]; //Los arreglos grandes es mejor compilarlos en global
std::vector<ll> primos;

void criba(){
  arr[1]=1;
  arr[2]=1;
  for (ll i = 3; i < 10001; i++)
    arr[i]=1;
  for (ll i = 2; i < 10001; i++) {
    if(arr[i]==1){
      primos.push_back(i);
      for (ll j = i*i; j < 10001; j+=i)
        arr[j] = 0;
    }
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
    return 0;
  }
