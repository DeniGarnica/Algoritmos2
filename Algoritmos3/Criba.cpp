#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll arr[1000001]; //Los arreglos grandes es mejor compilarlos en global

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  arr[1]=1;
  arr[2]=1;
  for (ll i = 3; i < 10001; i++) {
    arr[i]=1;
  }
  for (ll i = 2; i < 10001; i++) {
    if(arr[i]==1){
      std::cout << i << '\n';
      for (ll j = i*i; j < 10001; j+=i) {
        arr[j] = 0;
      }
    }
  }
    return 0;
  }
