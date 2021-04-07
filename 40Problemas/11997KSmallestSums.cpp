#include <algorithm>
#include <iostream>
using namespace std;

int main(void)
{
  int eof=1;
  int k,aux1, aux2;
  int cont=0;
  while(eof!=0){
    std::cin >> k;
    int A[k][k];
    int B[k*k];
    int M[k];
    int sum=0;
    cont=0;

    for (int i = 0; i < k; i++) {
      for (int j = 0; j < k; j++){
        std::cin >> A[i][j];
        if(j==0){
          M[i]=A[i][j];
        }else{
          if(M[i]>A[i][j])
            M[i]=A[i][j];
        }
      }
    }

    for (int i = 0; i < k; i++) {
      sum=sum+M[i];
      aux1=i;
      //std::cout << M[i] << '\n';
      for (int j = 0; j < k; j++){
        aux2=j;
        B[cont]=A[i][j]-M[i];
        cont++;
      }
    }

    sort(B,B+k*k);

    for (int i = 0; i < k; i++) {
      if(i==0){
        std::cout << sum;
      }else{
        std::cout << B[k+i-1]+ sum;
      }
      if(i<k-1){
        std::cout << " ";
      }
    }
    std::cout  << '\n';




  }


     return 0;
}
