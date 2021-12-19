#include<bits/stdc++.h>
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string name;
  long long prior;
  priority_queue<long long, string> cola;
  pair <long long, string> PAIR ;
  int i = 5;
  while(i) {
    cin>> name;
    if(name != "V"){
      cin>> prior;
      PAIR.first = prior;
      PAIR.second = name;
      cola.push(PAIR);
    }
    else{
      if(cola.empty())
        cout<< "\n";
      else{
        cout<< cola.top().second;
        cola.pop();
      }
    }
    i--;
  }
    return 0;
  }
