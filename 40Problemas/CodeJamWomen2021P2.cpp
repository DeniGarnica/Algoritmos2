#include <algorithm>
#include <iostream>
using namespace std;

int main(){
int t,n, bloq, res, aux, con,tam,aux2;
std::cin >> t;
for (int i = 0; i < t; i++) {
  res=1;
  aux=0;
  con=0;
  tam=0;
  std::cin >> n;
  int N[n];
  for (int o = 0; o < n; o++) {
    std::cin >> N[o];
    tam+=N[o];
  }
  char A[tam];
  A[0]='A';
  std::cout << "Case #"<< i+1<<": ";
  std::cout << A[con];
  con=1;
  for (int j = 0; j < n; j++) {
    if(j%2==0){
      for(int m = 0; m < N[j]; m++){
          A[con]='B'+m;
            if(m==N[j]-1 && j!=n-1){
              if(A[con]<'A'+N[j+1]){
                A[con]='A'+N[j+1];
              }
            }
          std::cout << A[con];
          con++;
        }
        }
      if(j%2==1){
        A[con]='A'+N[j]-1;
        std::cout << A[con];
        con++;
        for(int m = 1; m < N[j]; m++){
          A[con]=A[con-1]-1;
          std::cout << A[con];
          con++;

        }
      }
  }
  std::cout << '\n';
}
  return 0;
}
