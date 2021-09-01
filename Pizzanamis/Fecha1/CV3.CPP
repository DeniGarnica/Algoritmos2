#include<bits/stdc++.h>
using namespace std;


int main() {
  int k,m, n;
  std::cin >> k;
  for (int i = 0; i < k; i++) {
    std::cin >> m>>n;
    int res = n/log(n) - m/log(m);
    std::cout << res << '\n';
  }
  return 0;
}
