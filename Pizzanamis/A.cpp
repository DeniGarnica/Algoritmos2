#include<bits/stdc++.h>
using namespace std;

int main(){
  int cases, n, num;
  std::cin >> cases;
  for (int i = 0; i < cases; i++) {
    std::cin >> n;
    num=0;
    char A[n];
    for (int j = 0; j < n; j++) {
      std::cin >> A[j];
      if (A[j]==')') {
        num++;
      } else {
        if(A[j]!='\0')
          num=0;
      }
    }
    if(num>n-num){
      std::cout << "Yes" << '\n';
    }else{
      std::cout << "No" << '\n';
    }
  }

  return 0;
}
