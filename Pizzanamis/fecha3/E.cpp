#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ll num_ops, n_t, tt=0;
  cin >> num_ops;
  int dir = 2 , n_dir , actual, bandera=0;// dirección ficticia direccion entrante

  queue<ll> dir0;
  queue<ll> dir1;
  dir0.push(0);
  dir1.push(1);
  dir0.pop();
  dir1.pop();
  // leer primer valor

  cin >> n_t >> n_dir;
  tt = n_t + 10 ;
  dir = n_dir;

  for(int i=1; i< num_ops ; i++){
    cin >> n_t >> n_dir ;
    if (n_dir == 0) dir0.push(n_t);
    if (n_dir == 1) dir1.push(n_t);
  }

 while( !dir0.empty() || !dir1.empty() ){
  if (dir == 0){
    if (!dir0.empty()) {
      actual = dir0.front();
      if (tt-actual <= 0 ){// ya no alcanzo a subirse
        if(!dir1.empty()){
          dir = 1 ;
          bandera = 1;
        }else{
          tt = actual + 10;
        }
      }
      else{
        if (bandera==1){
          while( actual < tt ){
            if( !dir0.empty()){
               dir0.pop();
               actual = dir0.front();
            }
            else{
              dir = 1;
              bandera = 1;
              break;
            }
          }
          tt = tt + 10;
          bandera = 0;
        }
        else{
          tt = actual + 10;
          dir0.pop();
        }
      }
    }
    else{
      if (!dir1.empty()){
        dir = 1;
        bandera = 1;
      }
      else{
        cout << tt ;
        return 0;
      }
    }
  }


  if (dir==1){
     if (!dir1.empty() ) {
      //cout << "dirección es 1 \n ";
        actual = dir1.front();
        //cout << "actual " << actual << '\n';
        //cout << "tt-actual=" << tt-actual << '\n';
        if (tt-actual <= 0 ){// ya no alcanzo a subirse
          if(!dir0.empty()){
            dir = 0 ;
            bandera = 1;
          }else{
            tt = actual + 10;
          }
        }
        else{
          if (bandera==1){
            while(actual < tt && !dir1.empty()){
              if( !dir1.empty()){
               dir1.pop();
               actual = dir1.front();
            }
            else{
              dir = 1;
              bandera = 1;
              break;
            }
            }
            tt = tt + 10;
            bandera = 0;
          }
          else{
            tt = actual + 10;
            dir1.pop();
          }
        }
      }
      else{
        if (!dir0.empty()){
          dir = 0;
          bandera = 1;
        }
        else{
          cout << tt ;
          return 0;
        }
      }
  }

}
cout  << tt << '\n';


  return 0;
}
