#include <iostream>
using namespace std;

int main(){
  int t, n, m, res;
  char aux;
  std::cin >> t;
for (int i = 0; i < t; i++) {
  res=0;
  std::cin >> n>> m;
  char A[n][m];
  int B[m][4]; //Aqui guardaremos cuantas veces se repite cada letra por columna
  char C[m];
  for (int j = 0; j < n; j++) {
    for (int k = 0; k < m; k++) {
      if(j==0){
        B[k][0]=0;
        B[k][1]=0;
        B[k][2]=0;
        B[k][3]=0;
      }
      std::cin >> A[j][k];
      //la idea es que la cadena formada con las letras kas repetidas sera la que disminuya los errores.
      //POr ello calculamos cuantas vceces se repite cada letra por columna
      if(A[j][k]=='A')
        B[k][0]++;
      if(A[j][k]=='C')
        B[k][1]++;
      if(A[j][k]=='G')
        B[k][2]++;
      if(A[j][k]=='T')
        B[k][3]++;

    }
  }

  for (int k = 0; k < m; k++) {
    //Los errores son las veces que no coincide la que se eligio con la de la cadena, que es la cantidad de repeticiones que no se usaron
    if (B[k][0]<B[k][1]|| B[k][0]<B[k][2]||B[k][0]<B[k][3]) {
      if (B[k][1]<B[k][2]||B[k][1]<B[k][3]) {
        if (B[k][2]<B[k][3]) {
          C[k]='T';
          res+=B[k][1]+B[k][2]+B[k][0];
        }else{
          C[k]='G';
          res+=B[k][1]+B[k][0]+B[k][3];
        }
      }else{
        C[k]='C';
        res+=B[k][0]+B[k][2]+B[k][3];
      }
    }else{
      C[k]='A';
      res+=B[k][1]+B[k][2]+B[k][3];
    }
    std::cout << C[k];
  }
  std::cout << '\n';
  std::cout << res << '\n';
}

  return 0;
}
