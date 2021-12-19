#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll sum[1000002][2];
ll megas(string tam){
  int t;
  if(tam[tam.size()-1]=='M'){
    tam[tam.size()-1] = '\0';
    t= stoi(tam);
    return (ll)t;
  }
  if(tam[tam.size()-1]=='G'){
    tam[tam.size()-1] = '\0';
    t= stoi(tam);
    return (ll)t*1024;
  }
  if(tam[tam.size()-1]=='T'){
    tam[tam.size()-1] = '\0';
    t= stoi(tam);
    return (ll)t*1024*1024;
  }

}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_vid;
  string tam;
  std::cin >> num_vid;
  std::cin >> tam;
  ll total = megas(tam);
  ll max, min;
  sum[0][0] = 0;
  for(int i = 1; i <= num_vid; i++){
    cin>> sum[i][0];
    sum[i][0] += sum[i-1][0];
    sum[i][1]=-1;
  }
  if(sum[num_vid-1][0]<total){
    std::cout << num_vid <<" "<<"-1" <<'\n';
    return 0;
  }
  for(ll i = 0; i < num_vid; i++) {
    ll k = i+1;
    ll actual = sum[k][0] - sum[i][0];
    while(actual < total && k<num_vid){
      k++;
      actual = sum[k][0] - sum[i][0];
    }
    if(k!=num_vid){
    if(i==0){
      max = k-i;
      min = k-i;
    }else{
      if(k-i<max)
        max = k-i;
    }}
  }
  std::cout <<max<< '\n';
    return 0;
  }
