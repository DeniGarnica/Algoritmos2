#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos, n, m, s, i, j, k, res, avance;
  int bandera = 0;
  std::string A, B, C;
  std::cin >> num_casos;
  for (int o = 0; o < num_casos; o++) {
    std::cin >> A >> B >> C;
    n = A.size(); m = B.size(); s = C.size();
    i = 0; j = 0; k = 0; res = 0;
    for (int p = 0; p < s; p++){
      if(i <= n && j <= m){
        if(A[i] != B[j]){
            if(C[k] == A[i]){
                  //std::cout << "C["<<k<<"] == A["<<i<<"]" << '\n';
                  k++; i++;
            }else{
                  if(C[k] == B[j]){
                        //std::cout << "C["<<k<<"] == B["<<j<<"]" << '\n';
                        k++; j++;
                  }else{
                        break;
                  }
            }
        }else{
            avance = 1;
            while(i + avance < n && j + avance < m && A[i + avance] == B[j + avance] && A[i + avance] == C[k + avance]){
              avance++; //Avanzamos mientras los 3 sean iguales en su posicion actual y no se pasen de su tamano
            }
            //std::cout <<"avance = "<< avance << '\n';
            if(i + avance < n && j + avance < m){ //Si ninguno se pasa pero ya los 3 no son iguales
                if(A[i + avance] == C[k + avance]){
                    i += avance;
                    k += avance;
                }else{
                  if(B[j + avance] == C[k + avance]){
                      j += avance;
                      k += avance;
                  }else{
                    if(C[k + avance] == B[j]){
                      i += avance;
                      k += avance + 1;
                      j += 1;
                    }else{
                      break;
                    }
                  }
                }
            }else{
              if(i + avance == n && j + avance < m && B[j + avance] == C[k + avance]){
                //std::cout << "caso 2" << '\n';
                j += avance;
                k += avance;
              }else{
                if(j + avance == m && i + avance < n && A[i + avance] == C[k + avance]){
                  //std::cout << "caso 3" << '\n';
                  i += avance;
                  k += avance;
                }else{
                  if(i + avance == n && j + avance == m && A[i + avance -1] == B[j + avance -1] && A[i + avance -1] == C[k + avance-1]){
                    i += avance;
                    k += avance;
                  }else{
                    break;
                  }
                }
            }
            p+= avance - 1;
        }
      }
      }
    }
    if(i == n && j == m && n+m==s)
      res = 1;
    std::cout << res << '\n';
  }
    return 0;
  }
