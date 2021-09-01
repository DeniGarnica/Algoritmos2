#include<bits/stdc++.h>
using namespace std;

int main() {
  int num_ver, P_x,P_y;
  double eps=1e-9;
  std::cin >> num_ver;
  while (num_ver!=0) {
  int X[num_ver], Y[num_ver];
    for (size_t i = 0; i < num_ver; i++) {
      std::cin >> X[i] >> Y[i];
    }
    std::cin >> P_x>> P_y;
    for(int i=0,j=num_ver-1;i<num_ver;j=i++){
      if(Y[i]<=P_y+eps && P_y<Y[j] || Y[j]<=P_y+eps && P_y<Y[i]){
        if()
      }
    }

    std::cin >> num_ver;
  }
  return 0;
}
