#include <iostream>
#include <cmath>
using namespace std;

void braile(char a, string* A){
  switch(a) {
    case '1':
      A[0]="*.";
      A[1]="..";
      A[2]="..";
      break;
    case '2':
      A[0]="*.";
      A[1]="*.";
      A[2]="..";
      break;
    case '3':
      A[0]="**";
      A[1]="..";
      A[2]="..";
      break;
    case '4':
      A[0]="**";
      A[1]=".*";
      A[2]="..";
      break;
    case '5':
      A[0]="*.";
      A[1]="*.";
      A[2]="..";
      break;
    case '6':
      A[0]="**";
      A[1]="*.";
      A[2]="..";
      break;
    case '7':
      A[0]="**";
      A[1]="**";
      A[2]="..";
      break;
    case '8':
      A[0]="*.";
      A[1]="**";
      A[2]="..";
      break;
    case '9':
      A[0]=".*";
      A[1]="*.";
      A[2]="..";
      break;
    case '0':
      A[0]=".*";
      A[1]="**";
      A[2]="..";
      break;
}
}

int main() {
  int D=-1;
  char L;
  while (D!=0) {
    std::cin >> D;
    std::cout << D << '\n';
    std::cin >> L;
    if (L == 'S') {
      getchar();
      char A[D];
      string B[D][3];
      for (int i = 0; i < D; i++) {
        A[i]=getchar();
        braile(A[i], B[i]);
      }

      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < D; j++) {
          std::cout << B[j][i];
          if (j<D-1)
            std::cout << " ";
        }
        std::cout  << '\n';
      }

    } else {

    }
  }

  return 0;
}
