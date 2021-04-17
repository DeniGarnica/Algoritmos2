#include <algorithm>
#include <iostream>
using namespace std;

int main(){
int t,n,con,res,fres;
std::cin >> t;
for (int i = 0; i < t; i++) {
  con=1;
  res=1;
  fres=1;
  std::cin >> n;
  if(n!=0){
  int A[n];
  for (int j = 0; j < n; j++) {
    std::cin >> A[j];
  }
  sort(A,A+n);

  for (int j = 1; j < n; j++) {
    if (A[j-1]==A[j]) {
      res+=con;
    }else{
      con++;
      res+=con;
    }
  }
  std::cout << "Case #"<< i+1<<": "<<res << '\n';
}else{
  std::cout << "Case #"<< i+1<<": "<<0 << '\n';
}
}

  return 0;
}
