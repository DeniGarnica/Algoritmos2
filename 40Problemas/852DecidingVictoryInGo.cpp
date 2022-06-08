//Denisse Garnica Sanchez
//denisse.garnica@cimat.mx

#include<bits/stdc++.h>
#define ll long long
char Go_board[10][10];
bool visitado[10][10];


int dfs(int i, int j){
  if(i<0 || i>=9 || j<0 || j>=9) return 0; //Si se sale de los bordes
  if(Go_board[i][j] == 'X') return 1; //Marcamos si estamos en un borde negro
  if(Go_board[i][j] == 'O') return 2; //Marcamos si estamos en un borde blanco
  if(visitado[i][j]) return 0; //Si ya hemos vsitado la casilla
  visitado[i][j] = 1; //Marcamos como visitada
  int res = 0;
  res |= dfs(i+1, j); //Guardamos el resultado util
  res |= dfs(i-1, j);
  res |= dfs(i, j+1);
  res |= dfs(i, j-1);

  return res;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int num_casos;
  char aux;
  std::cin >> num_casos;
  for (size_t k = 0; k < num_casos; k++) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++)
      std::cin >> Go_board[i][j];
    }
    int p_blancas = 0;
    int p_negras = 0;
    int res;

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++)
        if(Go_board[i][j] == '.'){
          memset(visitado, 0, sizeof(visitado));
          //Cuando lleguemos aqui ya habremos llenado toda una zona
          res = dfs(i, j);
          if(res == 1) p_negras++;
          if(res == 2) p_blancas++;
        }else if(Go_board[i][j] == 'X'){
          p_negras++;
        }else if(Go_board[i][j] == 'O'){
          p_blancas++;
        }
    }
    std::cout << "Black "<< p_negras <<" White "<< p_blancas << '\n';
  }
    return 0;
  }
