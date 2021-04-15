#include <iostream>
using namespace std;
#include <math.h>

int main(){
  int n, a, b, r1, r2 ,res;
  while(cin){
  res=1;
  std::cin >>n>>a>>b;
  r1=ceil((a+a%2)/2);
  r2=ceil((b+b%2)/2);
  while(r1!=r2){
    res++;\
    if(r1!=0)
      r1=ceil((r1+r1%2)/2);
    if(r2!=0)
      r2=ceil((r2+r2%2)/2);
  }
  std::cout << res << '\n';

  }
  return 0;
}
