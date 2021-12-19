#include<bits/stdc++.h>
using namespace std;
#define ll long long

class DisjSet {
    ll *rank, *parent, n;

public:
    DisjSet(ll n)
    {
        rank = new ll[n];
        parent = new ll[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (ll i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    ll find(ll x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    ll rango(ll x){
      ll xset = find(x);
      return rank[xset];
    }

    void Union(ll x, ll y)
    {
        ll xset = find(x);
        ll yset = find(y);

        if (xset == yset)
            return;
        if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        }
        else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        }
        else {
            parent[yset] = xset;
            rank[xset] = rank[xset] + 1;
        }
    }
};


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ll num_estudiantes, num_parejas, es1, es2;
  std::cin >> num_estudiantes;
  std::cin >> num_parejas;
  ll num_pp = num_estudiantes - num_parejas;
  ll num_sinfrat = num_estudiantes;
  ll num_frat =0;
  ll aux = 0;
  DisjSet frats(num_estudiantes);
  for (ll i = 0; i < num_parejas; i++) {
    std::cin >> es1 >> es2;
    es1--;
    es2--;
    //std::cout << frats.find(es1)<< '\n';
    if (frats.rango(es1) == 0 && frats.rango(es2) == 0){
      num_frat++;
      //std::cout << "A" << '\n';
    }
    if (frats.rango(es1) != 0 && frats.rango(es2) != 0 && frats.find(es1) != frats.find(es2)){
      num_frat--;
      //std::cout << "B" << '\n';
    }
    //std::cout <<"padre: " <<frats.find(es1)<<" rango: "<<frats.rango(es1)<< '\n';
    //std::cout <<"padre: " <<frats.find(es2)<<" rango: "<<frats.rango(es2)<< '\n';
    if (frats.find(es1) == frats.find(es2)){
      aux++;
      //num_frat++;
      //std::cout << "C" << '\n';
    }
    frats.Union(es1, es2);
    //std::cout << "num pp: "<< num_pp << '\n';
    //std::cout << "num aux: "<< aux << '\n';
  }
  //std::cout << num_frat << '\n';
  //num_frat = num_pp - num_sinfrat;
  num_sinfrat =  num_pp - num_frat +  aux;
  std::cout << num_frat<< " " <<num_sinfrat << '\n';
    return 0;
  }
