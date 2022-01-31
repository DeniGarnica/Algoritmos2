#include<bits/stdc++.h>
using namespace std;
#define ll long long

template <class Key, class T> class UpdatableHeap{ //T es la clase de prioridades, Key es la clase de las claves.
  private:
    vector< pair<Key, T> >heap; //Guarda la clave y la prioriedad
    map<Key, ll> mapa; //Guarda la relacion de clave con el indice elemento del vector.

    ll Parent(ll i){ //devuelve el indice del padre en el vector
        if(i!=0){
            if(i%2==0)
                return (i/2)-1;
            return (i-1)/2;
        }
        return 0;
    }
    ll Left(ll i){ //devuelve el indice del hijo izquierdo en el vector
        return 2*i+1;
    }
    ll Right(ll i){//devuelve el indice del hijo derecho en el vector
        return 2*i+2;
    }

  public:
    void imprimeTodo(){
        ll tam = heap.size();
        for(ll i=0;i<tam;i++)
            cout << "index: " << mapa[heap[i].first]<< "  prioriedad: " << heap[i].second<< "  Clave: " << heap[i].first <<'\n';
    }

    bool emptyheap(){
        if(heap.size()==0)
            return 1;
        else
            return 0;
    }

    pair<Key, T> top() const{
        return heap[0];
    }

    void imprimeMap(){
      for (auto it = mapa.cbegin(); it != mapa.cend(); ++it) {
          std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
      }
    }

    void insertOrUpdate(const Key k, const T p){
        //mapa.count(k) nos da la cantidad de veces que esta el elemento k en el mapa.
        if(mapa.count(k)>0){ //Si la clave ya esta, cambia el valor
              int aux = mapa[k] ; //Nos da la posicion del elemento en el vector
              //ActualizaI(aux, p);
        }else{ //Si la clave no esta, insertala y ordena
              ll t = heap.size();
              mapa.insert(make_pair(k, t));
              heap.push_back(make_pair(k, p));
              //HeapifyDownUp(t);
        }
    }

    bool isInserted(const Key k){
          if(emptyheap()){
                return 0;
          }else{
                if(mapa.count(k)>0)
                    return 1;
                else
                    return 0;
          }
    }

    void eraseH(const Key K){//Le pasamos la clave y borra el elemento del heap.
          bool is = isInserted(K);
          if(is == 0){//Si no esta insertado, no hace nada
                return;
          }else{
                if(heap.size()==1){//En caso de tener un unico elemento solo lo saca
                      heap.pop_back();
                      mapa.clear();
                }else{ //En otro caso , intercambia el que se va a sacar y el ultimo, saca el ultimo, y reacomoda.

                      if(mapa[K]!=heap.size()-1){ //Si no es el ultimo, lo intercambia con el ultimo y lo saca
                            //intercambia(mapa[K], heap.size()-1)
                            heap.pop_back();
                            auto it=mapa.find(K);
                            mapa.erase(it);

                      }else{ //Si es el ultimo, solo lo saca
                            heap.pop_back();
                            auto it=mapa.find(K);
                            mapa.erase(it);
                      }
                }
          }
    }

    void pop(){//es equivalente a borrar el elemento 0.
        ll tam = heap.size();
        if(tam>0)
            eraseH(heap[0].first);
        else
            return;
  }

};




int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string action, food;
  ll n, cantidad;
  UpdatableHeap<string, ll> UHeap;
  cin >> n;
  for(ll k=0; k<n; k++){
        cin>>action;
        if(action=="P"){
            if(UHeap.emptyheap()){
                cout<<-1<<endl;
            }else{
                pair<string, ll> A = UHeap.top();
                cout<< A.first<< " " << A.second << '\n';
            }
        }
        if(action=="IU"){
            cin>> food;
            cin>> cantidad;
            UHeap.insertOrUpdate(food, cantidad);
        }
        if(action=="DL")
            UHeap.pop();
        if(action=="D"){
            cin>> food;
            if(UHeap.isInserted(food))
                UHeap.eraseH(food);
        }
  std::cout << "heap actual despues de la accion " <<action << '\n';
  UHeap.imprimeTodo();
  std::cout << "mapa actual:" << '\n';
  UHeap.imprimeMap();

  std::cout  << '\n';
  }
  return 0;
}
