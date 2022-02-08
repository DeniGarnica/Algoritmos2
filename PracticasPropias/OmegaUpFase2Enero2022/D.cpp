#include<bits/stdc++.h>
#include <wchar.h>
using namespace std;
#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, S;
  string D;
  std::cin >> N>>S >>D;
  int tiempo[N];
  int dia0;
  float t_total=0.0;
  string dia[7] = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
  for (int i = 0; i < 7; i++) {
    if(D[0]==dia[i][0]){
      if(i!=1){
        dia0=i;
        break;
      }else{
        if(D[1]==dia[i][1]){
          dia0=i;
          break;
        }
      }
    }
  }
  for (int i = 0; i < N; i++) {
    std::cin >> tiempo[i];
    t_total+=float(tiempo[i]);
  }
  float media = t_total/float(N);
  float desvi = 0.0;
  t_total = 0.0;
  for (int i = 0; i < N; i++)
    t_total += (float(tiempo[i])-media)*(float(tiempo[i])-media);
  desvi = sqrt(t_total/float(N));
  bool flag = 0;
  for (int i = 0; i <N; i++){
    if(tiempo[i]-desvi*S>media){
      std::cout << "Día #"<< i <<" - "<<dia[(i+dia0)%7]<<" - Más de los normal" << '\n';
      flag =1;
    }
    if(tiempo[i]+desvi*S<media){
      std::cout << "Día #"<< i <<" - "<<dia[(i+dia0)%7]<<" - Menos de los normal" << '\n';
      flag =1;
    }
  }

  if(flag == 0 )
    std::cout << "No hubo anomalías" << '\n';

    return 0;
  }
