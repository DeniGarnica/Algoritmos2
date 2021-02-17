#include <iostream>
#include <cmath>
#include <map>
using namespace std;

int main(){
  int n, num, numjugadores, serpientes, dados, inicio, fin, vdado, turno;
  int gameend=0;
  std::cin >> n;
  for(int i=0;i<n;i++){
    gameend=0;
    std::cin >> numjugadores;
    if(numjugadores==0){
      num = 1;
      gameend=1;
    }else{
      num = numjugadores;
    }
    int A[num];
    std::cin >> serpientes;
    std::cin >> dados;
    map<int, int> serpiente;
    for(int j=0;j<serpientes;j++){
      std::cin >> inicio;
      std::cin >> fin;
      serpiente.insert(pair<int, int>(inicio, fin));
    }
    for(int j=0;j<dados;j++){
      std::cin >> vdado;
      if(gameend==0){
      turno = j%num;
      if(j<numjugadores){
        A[turno]=vdado+1;
      }else{
        A[turno]=A[turno]+vdado;
      }
      if(serpiente.find(A[turno])!= serpiente.end()){//Si esta en el mapa
        A[turno]=serpiente[A[turno]];
      }
      if(A[turno]>=100){
        A[turno]=100;
        gameend=1;
      }
    }
    }
    if(dados<numjugadores){
      for(int j=dados;j<numjugadores;j++){
        A[j]=1;
      }
    }
    if(numjugadores>0){
    for(int j=0;j<numjugadores;j++){
      std::cout << "Position of player "<<j+1<<" is "<<A[j] << '\n';
    }}

  }
  return 0;
}
