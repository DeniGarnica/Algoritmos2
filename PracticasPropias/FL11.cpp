#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

long long getMaxAdditionalDinersCount(long long N, long long K, int M, vector<long long> S) {
  sort(S.begin(), S.end());
  ll tope = 1;
  ll actual = S[0]-K-1;
  ll res = 0;

  for(int i = 0; i < M; i++){
    res += floor(max((actual-tope-1), ll(0))/(K+1));
    tope = S[i];
    actual = S[i+1];
  }

  actual = N+1;
  tope = S[M-1];
  if(actual >= tope){
      res += floor(max((actual-tope-1), ll(0))/(K+1));
  }

  return res;
}


int main(){
  ll N = 10;
  ll K = 1;
  ll M = 2;
  vector<long long> S;
  S.push_back(2);
  S.push_back(6);
  ll res = getMaxAdditionalDinersCount(N, K, M, S);
  std::cout << res << '\n';
  return 0;
}
