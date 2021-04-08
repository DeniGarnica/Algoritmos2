#include <algorithm>
#include <iostream>
using namespace std;

int main(void)
{
  int k,aux1, aux2,cont2;
  int cont=0;
  int zeros=0;
  while(cin){
    std::cin >> k;
    int A[k][k];
    int B[k*k];
    int M[k];
    int sum=0;
    zeros=0;
    cont=0;
    cont2=0;

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
        if(B[cont-1]==0) {
          zeros++;
        }
      }
    }
    zeros-=k;

    std::cout  << '\n';
    for (int i = 0; i < k*k; i++) {
      std::cout << B[i] << " ";
      if (i%k==k-1) {
        std::cout  << '\n';
      }
    }
    std::cout << '\n';

    sort(B,B+k*k);

    std::cout  << '\n';
    for (int i = 0; i < k*k; i++) {
      std::cout << B[i] << " ";
      if (i%k==k-1) {
        std::cout  << '\n';
      }
    }
    std::cout << '\n';


    for (int i = 0; i <k; i++) {
      if(i==0){
        std::cout << sum;
        if(i<k-1)
          std::cout << " ";
      }else{
        if(B[k+cont2]==0){
          std::cout << sum;
          cont2++;
          if(i<k-1)
            std::cout << " ";
        }else{
          for (int j = 0; j < zeros+1; j++) {
            //std::cout << "j: "<< j << '\n';
            //std::cout << "i+j: "<<i+j << '\n';
            if (i+j<=k){
              std::cout << B[k+cont2]+ sum;
              if(i<k-1)
                std::cout << " ";
              }
              //std::cout <<"i: "<<i << '\n';
              i++;
            }
            cont2++;
            i--;
        }
        }
    }
    std::cout  << '\n';
  }
     return 0;
}
