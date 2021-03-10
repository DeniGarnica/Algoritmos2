#include <iostream>
#include <vector>
using namespace std;

int subsize(int i, vector<vector<int>> hijos, int *subarbolsize){
  if(hijos[i].empty()){
    subarbolsize[i]=1;
    std::cout << "Tam del arbol"<< i<<": " << subarbolsize[i]<< '\n';
    return 1;
  }else{
    int aux=0;
    for (size_t j = 0; j < hijos[i].size(); j++) {
      aux = aux+ subsize(hijos[i][j], hijos, subarbolsize);
    }
    subarbolsize[i] = aux+1;
    std::cout << "Tam del arbol"<< i<<": " << subarbolsize[i]<< '\n';
    return subarbolsize[i];
  }
}

int main(){
  int n, q;
  std::cin >> n >> q;
  int A[n];
  int padre[n];
  vector<vector<int>> hijos;
  int subarbolsize[n];
  padre[0]=0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> A[i];
    hijos.push_back({});
  }
  for (size_t i = 0; i < n-1; i++) {
    std::cin >> padre[i+1];
    hijos[padre[i+1]].push_back(i+1);
  }
  for (size_t i = 0; i < n-1; i++) {
    std::cout << i<<": ";
    if(!hijos[i].empty()){
      for (size_t j = 0; j < hijos[i].size(); j++) {
        std::cout << hijos[i][j]<<" ";
      }
    }
    std::cout  << '\n';
  }

  std::cout << subsize(0, hijos, subarbolsize) << '\n';
  return 0;
}
