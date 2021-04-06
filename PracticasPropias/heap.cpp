#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template <class T, class Key> class Heap{
  private:
  public:
    vector<T>heap;
    vector<Key>info;

int Parent(int i){
    return (i-1)/2;
}
int Left(int i){
    return 2*i+1;
}
int Right(int i){
    return 2*i+2;
}
void Insert(T n, Key in){
    heap.push_back(n);
    info.push_back(in);
    int t = heap.size();
    HeapifyDown(t-1);
}
void swapi(int a, int b){
  T aux1=heap[a];
  Key aux2=info[b];
  heap[a]=heap[b];
  info[a]=info[b];
  heap[b]=aux1;
  info[b]=aux2;
}
void HeapifyDown(int i){ //Checa si su padre es mayor
  if(heap[Parent(i)]<heap[i]){
    swapi(i,Parent(i));
    Heapify(Parent(i));
  }
}
void HeapifyUp(int i){ //Checa si sus hijos son mayores
  if(heap[Left(i)]>heap[i] && heap[Left(i)]>heap[Right(i)]){
    swapi(i,Left(i));
    Heapify(Left(i));
  }else{
    if(heap[Right(i)]>heap[i] && heap[Left(i)]<heap[Right(i)]){
      swapi(i,Right(i));
      Heapify(Right(i));
    }
  }
}
void ActualizaI(int i, T newValue){
  T aux = heap[i];
  heap[i]=newValue;
  if(aux>newValue){
    HeapifyUp(i); //Si el nuevo valor es menor, checa su relacion con los hijos
  }else{
    HeapifyDown(i); //Si el nuevo valor es mayor, checa su relacion con el padre
  }

}


Key EliminaMax(){
    if(heap.size()==1){
        Key aux = info[0];
        heap.pop_back();
        info.pop_back();
        return aux;
    }else{
        if(heap.size()==0){
            return NULL;
        }else{
            Key aux = info[0];
            heap[0]=heap[heap.size()-1];
            info[0]=info[info.size()-1];
            heap.pop_back();
            info.pop_back();
            HeapifyUp(0);
            return aux;
        }
    }
}
bool emptyheap(){
    if(heap.empty()){
        return 1;
    }else{
        return 0;
    }
}
};

int main(){
    return 0;
  }
