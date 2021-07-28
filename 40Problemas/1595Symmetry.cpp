#include <iostream>
#include <cmath>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

bool sort2(const pair<int,int> &a, const pair<int,int> &b){
    if(a.first == b.first){
      return (a.second < b.second);
    }else{
      return (a.first < b.first);
    }
}

bool sort3(const pair<int,int> &a, const pair<int,int> &b){
  if(a.first == b.first){
    return (a.second > b.second);
  }else{
    return (a.first < b.first);
  }
}

int main(){
int T, num_dots, min_x, max_x, dist_y;
float eje;
bool primera = 1;
std::cin >> T;

while (T--) {
  //if (!primera) std::cout<<'\n';
  primera=0;
  std::cin >> num_dots;
  vector<pair <int, int> > vect;
  int A[2][num_dots];
  int dist_x = 0;
  bool flag =1;
  for (size_t i = 0; i < num_dots; i++) {
    std::cin >> A[0][i];
    std::cin >> A[1][i];
    vect.push_back(make_pair(A[0][i],A[1][i]));
    if(i==0||A[0][i]<min_x)
      min_x = A[0][i];
    if(i==0||A[0][i]>max_x)
      max_x = A[0][i];

  }
  if(num_dots==1){
    std::cout << "YES"<< '\n';
  }else{
    //Las siguientes 4 lineas son para eliminar puntos duplicados, si e eliminan dan respuestas completamente distintas
    /*sort(vect.begin(), vect.end(), sort2);
    auto last = unique(vect.begin(), vect.end());
    vect.erase(last, vect.end());
    num_dots=vect.size();*/

    dist_x=0;
    for (int i = 0; i < num_dots; i++) {
      dist_x+=vect[i].first;
    }
    eje = (float)(min_x + max_x)/2; //Aqui debe esatr el eje de simetria
    if ((float)dist_x == eje*num_dots){ //para que exista simetria el promedio de las distnacias al eje debe ser el eje mismo

      sort(vect.begin() + ceil(num_dots/2) , vect.end(), sort3);
      //for (size_t i = 0; i < num_dots; i++) {std::cout << vect[i].first<<", "<<vect[i].second << '\n';}
    for (size_t i = 0; i < ceil(num_dots/2); i++) {
      if(vect[i].first < eje){
        //std::cout << vect[num_dots-1-i].first<< " | " << (eje*2 -vect[i].first)  <<'\n';
        //std::cout << vect[num_dots-1-i].second <<" | " << vect[i].second<< '\n';
        if(vect[num_dots-1-i].first != (eje*2 -vect[i].first) || vect[num_dots-1-i].second!= vect[i].second){
          std::cout << "NO"<< '\n';
          flag = 0;
          break;
        }
      }
    }
      if(flag)
        std::cout << "YES"<< '\n';
    }else{
      std::cout << "NO"<< '\n';
    }
  }
}

    return 0;
}
