#include<bits/stdc++.h>
using namespace std;

int main(){
 int cases, lado, n_puntos, x, y, resultado;
 std::cin >> cases;
 for (int i = 0; i < cases; i++) {
   std::cin >> lado;
   std::cin >> n_puntos;
   int X[lado], Y[lado], A[n_puntos][2], vertical_p[n_puntos];
   int vertical =0;
   int aux=0;
   for (int k = 0; k < lado; k++) {
     X[k]=0;
     Y[k]=0;
     vertical_p[k]=0;
   }
   for (int j = 0; j < n_puntos; j++) {
     std::cin >> x;
     std::cin >> y;
     A[j][0]=x;
     A[j][1]=y;
     if(x==y){
       vertical++;
       vertical_p[j]=1;
     }
     X[x-1]=1;
     Y[y-1]=1;
   }
   for (int j = 0; j < lado; j++) {
     if(X[j]!=Y[j]){
       aux=1;
       break;
     }
   }
   if(aux==0){
     if(vertical==n_puntos){
       resultado = 0;
     }else{
       int aux=0;
       while(X[aux]!=0){
         aux++;ee
       }
       X[]=
       resultado = n_puntos - vertical + 1;
     }
   }else{
     resultado = n_puntos -  vertical;
   }

   std::cout << resultado << '\n';
 }
  return 0;
}
