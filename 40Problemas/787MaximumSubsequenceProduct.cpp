#include<bits/stdc++.h>
#define ll long long
ll DP[105][105]; //Calcula el producto desde i a j
int nums[105];

void pre_DP(int n){
  int x = 1; int y;
  for (int i = 1; i < n; i++){
    x++; y=x;
    for (int j = 1; j < n-i; j++){
      DP[j][y] = DP[j+1][y]*DP[j][j];
      y++;
    }
    }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N;
  int nums[110];
  while(std::cin>>N){
    memset(nums, 0, sizeof(nums));
    DP[0][0] = N;
    int i = 1;
    ll res = N;
    while(std::cin>>N && N != -999999){
      DP[i][i] = N; //lenamos la diagonal de la DP
      if(res < N) res = N;
      i++;
    }
    pre_DP(i);
    ll actual = res;
    //Vamos probando todas las posibles subsecuencias y ver cual es mayor
    for (int j = 0; j < i; j++) {
      actual = DP[j][i-1];
      if(res < actual) res = actual;
    }
    std::cout << res << std::endl;
  }
    return 0;
  }
