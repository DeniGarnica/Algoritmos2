#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_prof;
  ll num_alum;
  ll A[6];
  ll B[6];
  int n = 0;
  char calificacion;
  std::cin >> num_prof;
  for (int i = 0; i < num_prof; i++) {
    if(i==0){
      for (int k = 0; k < 6; k++) {
        A[k] = 0;
      }
    }
    std::cin >> num_alum;
    for (ll j = 0; j < num_alum; j++) {
      if(j==0){
        for (int k = 0; k < 6; k++) {
          B[k] = 0;
        }
      }
      std::cin >> calificacion;
      if(calificacion=='A'){
        A[0]++;
        B[0]++;
      }
      if(calificacion=='B'){
        A[1]++;
        B[1]++;
      }
      if(calificacion=='C'){
        A[2]++;
        B[2]++;
      }
      if(calificacion=='D'){
        A[3]++;
        B[3]++;
      }
      if(calificacion=='E'){
        A[4]++;
        B[4]++;
      }
      if(calificacion=='F'){
        A[5]++;
        B[5]++;
      }
    }
    std::cout << "A:" <<B[0]<<" B:"<<B[1]<<" C:"<<B[2]<<" D:"<<B[3]<<" E:"<<B[4]<<" F:"<<B[5] << '\n';
  }
  std::cout << "TOTAL: "<<"A:" <<A[0]<<" B:"<<A[1]<<" C:"<<A[2]<<" D:"<<A[3]<<" E:"<<A[4]<<" F:"<<A[5] << '\n';

    return 0;
  }
