#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int n=0;
  int a,b,c;
  cin>>n;
  for(int i=0; i<n; i++){
    cin>>a>>b>>c;
    int men = min(a, min(b,c));
    int may = max(a, max(b,c));
    if(a!=men && a!=may){
      cout<<"Case 1: "<< a<<'\n';
    }else{
      if(b!=men && b!=may){
        cout<<"Case 2: "<< b<<'\n';
      }else{
        cout<<"Case 3: "<< c<<'\n';
      }
    }
  }
  return 0;
}
