#include<bits/stdc++.h>
#define ll long long
#define MAX 10000
int D[MAX][MAX]; //Guarda los optimos

//Vemos cual fue la forma de llegar al optimo
void backtracking(std::string &s1, std::string &s2){
  int n = s1.size(); int m = s2.size();
  char res[n+m];
  int i = n; int j = m; int actual = 0;
  while(i >= 1 && j >= 1){
    if(s1[i-1]==s2[j-1] && D[i][j] == D[i-1][j-1]){
        res[actual] = 'I';
        i--;j--;
        actual++;
    }else if(s1[i-1] != s2[j-1] && D[i][j] == D[i-1][j-1] + 1){
        res[actual] = 'S';
        i--;j--;
        actual++;
    }else if(D[i][j] == D[i][j-1]+1){
        res[actual] = 'A';
        j--;
        actual++;
    }else if(D[i][j] == D[i-1][j]+1){
        res[actual] = 'E';
        i--;
        actual++;
    }else{
        res[actual] = 'T';
        i -= 2; j -= 2;
        actual++;
    }
  }
    while(i==0 && j!=0){
      res[actual] = 'A';
      j--;
      actual++;
    }

    while(j==0 && i!=0){
      res[actual] = 'E';
      i--;
      actual++;
    }

    res[actual] = '\0';


  //Ya que la calculamos al reves, la imprimimos asi
  for (int k = 0; k < actual; k++)
    std::cout << res[actual - k - 1];
  std::cout  << '\n';
}

int DP(std::string &s1, std::string &s2){
  int n = s1.size();
  int m = s2.size();

  int max_dis = m + n;
  int db, k, l, cost, aux;
  for (int i = 0; i <= n; i++)
    D[i][0] = i;
  for (int i = 0; i <= m; i++)
    D[0][i] = i;

  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      if (s1[i-1] == s2[j-1]){
        cost = 0;
      }else{
        cost = 1;}
      int a = D[i-1][j-1] + cost;  //match o miss match
      int b = D[i][j-1] + 1;  //insertion
      int c = D[i-1][j] + 1; //deletion from a to b
      int d = max_dis;
      if(i - 2 >= 0 && j - 2 >= 0 && s1[i-1] == s2[j-2] && s1[i-2] == s2[j-1])
        d = D[i-2][j-2] + 1;  //transposition
      aux = std::min(std::min(a,b), std::min(c,d));
      D[i][j] = aux;
    }
  }
  return D[n][m];
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string S1, S2;
  int num_casos;
  std::cin >> num_casos;
  for (int i = 0; i < num_casos; i++) {
    std::cin >> S1 >> S2;
    std::cout << DP(S1, S2) << '\n';
    backtracking(S1, S2);
  }
    return 0;
  }
