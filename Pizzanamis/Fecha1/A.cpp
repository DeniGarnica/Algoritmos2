#include<bits/stdc++.h>
using namespace std;
float area(int a, int b, int c){
  float s = (a+b+c)/2;
  float result = sqrt(s*(s-a)*(s-b)*(s-c));
  return result;
}

int main(){
  int num_b, num_tri, a, b, c, k;
  std::cin >> num_b>> num_tri;
  int K[num_b], P[num_b];
  float N[num_tri], total_p;
  for (int i = 0; i < num_b; i++) {
    std::cin >> k >> P[i];
    K[i]=P[i]/k;
  }
  total_p=0;
  for (int j = 0; j < num_tri; j++) {
    std::cin >> a>>b>>c;
    N[j] = area(a,b,c);
    total_p+=N[j];
  }
  float total_k=total_p/30;
  std::cout << total_k << '\n';
  return 0;
}
