//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long
#define MAX 1500000
ll arr[MAX];
std::vector<ll> primos;

//precalculamos los primos
void criba(){
  arr[1]=1;
  arr[2]=1;
  for (ll i = 3; i < MAX; i++)
    arr[i]=1;
  for (ll i = 2; i < MAX; i++) {
    if(arr[i]==1){
      primos.push_back(i); //guadamos los rpimos
      for (ll j = i*i; j < MAX; j+=i)
        arr[j] = 0;
    }
  }
}

int solve(ll n){
  if(arr[n])
    return 0;
  ll res = 1;
  ll i = n;
  //Contamos el gap hasta llegar al primo anterior
  while(!arr[i]){
    res++;
    i--;
  }
  //y luego hasta el primo siguiente
  i = n+1;
  while(!arr[i]){
    res++;
    i++;
  }
  return res;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  ll N;
  criba(); //precalculamos los primos
  while(std::cin>>N  && N != 0){
    std::cout << solve(N) << '\n';
  }
    return 0;
}
