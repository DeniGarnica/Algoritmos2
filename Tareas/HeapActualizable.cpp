#include<iostream>
#include<cmath>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

template <class T, class Key> class UpdatableHeap{
  private:
    vector<T>heap; //Este vector guarda las prioridades
    vector<Key>info; //Este vector guarda la informacion de las prioridades
    map<Key, int> mapa; // En este mapa guardaremos la relacion entre las claves y su posicion en el vector heap, es decir la posicion en el vactor
    int Parent(int i){
      if(i!=0){
        if(i%2==0){
          return (i/2)-1;
        }else{
          return (i-1)/2;
        }
      }else{
        return 0;
      }
    }
    int Left(int i){
        return 2*i+1;
    }
    int Right(int i){
        return 2*i+2;
    }
    void swapi(int a, int b){ //Esta funcion hace todos los intercambios necesariuos
      int tam = info.size();
      int tam2 = heap.size();
      if(tam>a && tam>b && tam2>a && tam2>b){ //Para asegurarnos que esisten estos elementos en el vector
      if(mapa.find(info[a])!= mapa.end() && mapa.find(info[b])!= mapa.end()){ //Para asegurarnos que esisten estos elementos en el mapa
        if(mapa[info[a]]!=-1){
          mapa[info[a]]=b;}
        if(mapa[info[b]]!=-1){
          mapa[info[b]]=a;}
        T aux1=heap[a];
        Key aux2=info[a];
        heap[a]=heap[b];
        info[a]=info[b];
        heap[b]=aux1;
        info[b]=aux2;
      }}
    }
    void HeapifyDownUp(int i){ //Checa si su padre es mayor y reacomoda
    if(i!=0){//Si es cualquier otro que no sea la raiz, tiene un padre.
      if(heap[Parent(i)]<heap[i]){//Si el padre es menor, swap
        swapi(i,Parent(i));
        HeapifyDownUp(Parent(i));//si hubo un cambio, checa ahora con el nuevo padre.
      }else{
        if(heap[Parent(i)]==heap[i]){ //Si tienen la misma prioriedad acomoda segun la clave
          if(info[Parent(i)]<info[i]){
            swapi(i,Parent(i));
          }
        }
      }
    }
  }
    void HeapifyUpDown(int i){ //Checa si sus hijos son mayores
      int tam = heap.size();
      if(tam>2*i+2){ //De esta manera nos aseguramos que tanto el hijo izquierdo como el derecho existan
        if(heap[Left(i)]>heap[i] && heap[Left(i)]>heap[Right(i)]){
          swapi(i,Left(i));
          HeapifyUpDown(Left(i));
        }else{
          if(heap[Right(i)]>heap[i] && heap[Left(i)]<=heap[Right(i)]){
            swapi(i,Right(i));
            HeapifyUpDown(Right(i));
          }
        }
      }else{
        if(tam==2*i+2){ //En caso de que solo exista el hijo izquierdo
          if(heap[Left(i)]>heap[i]){
            swapi(i,Left(i));
          }
        }
      }
  }
    void ActualizaI(int i, T newValue){ //Cambia el dato y reacomoda
      T aux = heap[i];
      heap[i]=newValue;
      if(aux>newValue){
        HeapifyUpDown(i); //Si el nuevo valor es menor, checa su relacion con los hijos
      }else{
        if(aux<newValue)
          HeapifyDownUp(i); //Si el nuevo valor es mayor, checa su relacion con el padre
      }

    }
public:
    bool emptyheap(){
      if(heap.empty()){
        return 1;
      }else{
        return 0;
      }
    }
    void insertOrUpdate(const T p, const Key k){
      if(mapa.find(k)!= mapa.end()){ //Si la clave ya esta, cambia el valor
        T aux = mapa[k] ; //Nos da la posicion del elemento en el vector
        ActualizaI(aux, p);
      }else{ //Si la clave no esta, insertala y ordena
        int t = heap.size();
        mapa.insert(make_pair(k, t));
        heap.push_back(p);
        info.push_back(k);
        HeapifyDownUp(t);
  }
}
    bool isInserted(const Key k){
      if(emptyheap()){
        return 0;
      }else{
      if(mapa.find(k)!= mapa.end()){ //Si la clave alguna vez a estado
        int aux = mapa[k];
        if(aux==-1){
          return 0;
        }else{
          return 1;
        }
      }else{ //Si la clave nunca ha estado
        return 0;
      }
    }
    }
    pair<T, Key> top() const{
        pair <T, Key> top0;
        T aux1=heap[0];
        Key aux2=info[0];
        top0 = make_pair(aux1, aux2);
        return top0;
    }
    int getSize(){
      return heap.size();
    }
    void imprimeTodo(){
      for(int i=0;i<heap.size();i++){
        cout << "mapa: " << mapa[info[i]]<< "  heap: " << heap[i]<< "  info: " << info[i]<<'\n';
      }
    }
    void imprimeMap(){
      for (auto it = mapa.cbegin(); it != mapa.cend(); ++it) {
          std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
      }
    }
    void eraseH(const Key K){
      bool is = isInserted(K);
      if(is == 0){//Si no esta insertado, no hace nada
        return;
      }else{
        if(heap.size()==1){//En caso de tener un unico elemento solo lo saca
          mapa[info[0]]=-1;
          heap.pop_back();
          info.pop_back();
          mapa.clear();
        }else{//En otro caso , intercambia el que se va a sacar y el ultimo, saca el ultimo, y reacomoda.
          int aux = mapa[K];
          int tam = heap.size()-1;
          mapa[K]=-1;
          if(aux!=tam){ //Si no es el ultimo, lo intercambia con el ultimo y lo saca
            swapi(aux, tam);
            heap.pop_back();
            info.pop_back();
            HeapifyUpDown(aux);
          }else{//Si es el ultimo, solo lo saca
          heap.pop_back();
          info.pop_back();
          }
        }
      }
    }
    void pop(){//es equivalente a borrar el elemento 0.
      int tam = heap.size();
      if(tam>0){
        eraseH(info[0]);
      }else{
        return;
      }
  }
};

int main(){
     string action, food;
     int n,cantidad;
     UpdatableHeap <int, string> UHeap;
     cin >> n;
     for(int k=0; k<n; k++){
      cin>>action;
         if(action=="P"){
           if(UHeap.emptyheap()){
             cout<<-1<<endl;
           }else{
             pair<int, string> A = UHeap.top();
             cout<< A.second<< " " << A.first <<endl;
           }
         }
         if(action=="IU"){
           cin>> food;
           cin>> cantidad;
           UHeap.insertOrUpdate(cantidad, food);
         }
         if(action=="DL"){
           UHeap.pop();
         }
         if(action=="D"){
           cin>> food;
           if(UHeap.isInserted(food)){
             UHeap.eraseH(food);
           }
    }
  }
  return 0;
}
