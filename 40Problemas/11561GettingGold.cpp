#include<bits/stdc++.h>
#include <stack>
using namespace std;
#define ll long long

void printStack(stack<pair<int,int>> s){
	while(!s.empty()){
      cout<<"("<<s.top().first<<" "<<s.top().second<<")";
      s.pop();
    }
    cout<<"\n";
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n =0;
  int a, b, vecinos;
  while(cin >> a >> b){
    n++;
    int gold = 0;
    int A[50][50];
    char Maze[50][50];
    int x, y;
    stack<pair<int, int>> Pila;

    for (int i = 0; i < b; i++) {
      for (int j = 0; j < a; j++){
        std::cin >> Maze[i][j];
        A[i][j] = 0; //Iniciamos todos los nodos como no visitados
        if(Maze[i][j] == 'P'){ //Guardamos la posicion inicial
          x = j;
          y = i;
    }}}

    pair<int, int> actual;

    Pila.push(make_pair(x, y));

    while (!Pila.empty()) {
      actual = Pila.top();
      Pila.pop();
      x = actual.first;
      y = actual.second;
      //VAmos a hacer una DFS la cual se detiene si siente una trampa cerca
      if(A[y][x]!=1){
        //Vemos que ninguno de los vecinos sea trampa para ver si ponerlos en la cola o no. Pues si alguno es trampa
        int vecinos = 1;
        if(x-1>=0 && x-1<a && Maze[y][x-1] == 84) //Si esta dentro de los limites y es una trampa el vecino
          vecinos = 0;
        if(x+1>=0 && x+1<a && Maze[y][x+1] == 84)
          vecinos = 0;
        if(y-1>=0 && y-1<b && Maze[y-1][x] == 84)
          vecinos = 0;
        if(y+1>=0 && y+1<b && Maze[y+1][x] == 84)
          vecinos = 0;

        if(vecinos == 1){

          if(x-1>=0 && x-1<a && Maze[y][x-1] != '#' && A[y][x-1] != 1 ) {//Si esta dentro de los limites, no es una pared, y no esta visitado
            Pila.push(make_pair(x-1, y));
          }
          if(x+1>=0 && x+1<a && Maze[y][x+1]!= '#' && A[y][x+1] != 1 ) {
            Pila.push(make_pair(x+1, y));
          }
          if(y-1>=0 && y-1<b && Maze[y-1][x] != '#' && A[y-1][x] != 1 ) {
            Pila.push(make_pair(x, y-1));
          }
          if(y+1>=0 && y+1<b && Maze[y+1][x] != '#' && A[y+1][x]!= 1 ) {
            Pila.push(make_pair(x, y+1));
          }
        }

        if(Maze[y][x] == 'G')
          gold++;

        A[y][x] = 1; //Marcamos como visitado
      }
    }

    std::cout << gold << '\n';

    }

    return 0;
  }
