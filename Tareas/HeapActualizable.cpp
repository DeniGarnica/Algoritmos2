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
      if(mapa.count(info.at(a))>0 && mapa.count(info.at(b))>0){ //Para asegurarnos que esisten estos elementos en el mapa
        if(mapa[info.at(a)]!=-1){
          mapa[info.at(a)]=b;}
        if(mapa[info.at(b)]!=-1){
          mapa[info.at(b)]=a;}
        T aux1=heap.at(a);
        Key aux2=info.at(a);
        heap.at(a)=heap.at(b);
        info.at(a)=info.at(b);
        heap.at(b)=aux1;
        info.at(b)=aux2;
      }}
    }
    void HeapifyDownUp(int i){ //Checa si su padre es mayor y reacomoda
    if(i!=0){//Si es cualquier otro que no sea la raiz, tiene un padre.
      if(heap.at(Parent(i))<heap.at(i)){//Si el padre es menor, swap
        swapi(i,Parent(i));
        HeapifyDownUp(Parent(i));//si hubo un cambio, checa ahora con el nuevo padre.
      }else{
        if(heap.at(Parent(i))==heap.at(i)){ //Si tienen la misma prioriedad acomoda segun la clave
          if(info.at(Parent(i))<info.at(i)){
            swapi(i,Parent(i));
            HeapifyDownUp(Parent(i));
          }
        }
      }
    }
  }
    void HeapifyUpDown(int i){ //Checa si sus hijos son mayores
      int tam = heap.size();
      if(tam>2*i+2){ //De esta manera nos aseguramos que tanto el hijo izquierdo como el derecho existan
        if(heap.at(Left(i))>heap.at(i) && heap.at(Left(i))>heap.at(Right(i))){
          swapi(i,Left(i));
          HeapifyUpDown(Left(i));
        }else{
          if(heap.at(Right(i))>heap.at(i) && heap.at(Left(i))<=heap.at(Right(i))){
            swapi(i,Right(i));
            HeapifyUpDown(Right(i));
          }else{
            if(heap.at(Right(i))==heap.at(i)){
              if(heap.at(Left(i))==heap.at(i)){//Si tiene la misma prioriedad con ambos hijos
                if(info.at(Right(i))>info.at(Left(i))){
                  if(info.at(Right(i))>info.at(i)){
                    swapi(i,Right(i));
                    HeapifyUpDown(Right(i));
                  }
                }else{
                  if(info.at(Left(i))>info.at(i)){
                    swapi(i,Left(i));
                    HeapifyUpDown(Left(i));
                  }
                }

              }else{//Si tiene la misma prioriedad solo con el derecho, acomoda segun la clave
                if(info.at(Right(i))>info.at(i)){
                  swapi(i,Right(i));
                  HeapifyUpDown(Right(i));
                }
              }
            }
          }
        }
      }else{
        if(tam==2*i+2){ //En caso de que solo exista el hijo izquierdo
          if(heap.at(Left(i))>heap.at(i)){
            swapi(i,Left(i));
          }else{
            if(heap.at(Left(i))==heap.at(i)){ //Si tienen la misma prioriedad, acomoda segun la clave
              if(info.at(Left(i))>info.at(i)){
                swapi(i,Left(i));
                HeapifyUpDown(Left(i));
              }
            }
          }
        }
      }
  }
    void ActualizaI(int i, T newValue){ //Cambia el dato y reacomoda
      T aux = heap.at(i);
      heap.at(i)=newValue;
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
      if(mapa.count(k)>0){ //Si la clave ya esta, cambia el valor
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
      if(mapa.count(k)>0){ //Si la clave alguna vez a estado
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
        T aux1=heap.at(0);
        Key aux2=info.at(0);
        top0 = make_pair(aux1, aux2);
        return top0;
    }
    int getSize(){
      return heap.size();
    }
    void imprimeTodo(){
    int tam = heap.size();
      for(int i=0;i<tam;i++){
        cout << "mapa: " << mapa[info.at(i)]<< "  heap: " << heap.at(i)<< "  info: " << info.at(i)<<'\n';
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
          mapa[info.at(0)]=-1;
          heap.pop_back();
          info.pop_back();
          mapa.clear();
        }else{//En otro caso , intercambia el que se va a sacar y el ultimo, saca el ultimo, y reacomoda.
          int aux = mapa[K];
          int tam = heap.size()-1;
          T aux2= heap.at(aux);
          mapa[K]=-1;
          if(aux!=tam){ //Si no es el ultimo, lo intercambia con el ultimo y lo saca
            swapi(aux, tam);
            heap.pop_back();
            info.pop_back();
            if(heap.at(aux)>=aux2){//Si la prioridad del que estaba al ultimo, es mayor de la prioridad del que se acaba de sacar, checa la relacion con su padre
              if(aux!=0){
              HeapifyDownUp(aux);
              }else{
                HeapifyUpDown(aux);
              }

            }else{
              if(heap.at(aux)<aux2){//Si la prioridad del que estaba al ultimo, es menor de la prioridad del que se acaba de sacar, checa la relacion con sus hijos
                HeapifyUpDown(aux);
              }
            }
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
        eraseH(info.at(0));
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
    //UHeap.imprimeTodo();
    //UHeap.imprimeMap();
  }
  return 0;
}
