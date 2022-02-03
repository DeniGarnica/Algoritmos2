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

    void intercambia(ll a, ll b){ //le pasamos los indices en el heap y los intercambia de posicion
          pair<Key, T> aux = heap[a];
          ll aux_map = mapa[heap[a].first];
          mapa[heap[a].first] =  mapa[heap[b].first];
          mapa[heap[b].first] = aux_map;
          heap[a] = heap[b];
          heap[b] = aux;
    }
    void Heapify_Down_to_Up(ll i){ //Checa si su padre es mayor y reacomoda, le pasamos el indice de donde va a checar.
        if(i==0) //Si es la raiz, no hace nada.
            return;
        if(heap[Parent(i)].second< heap[i].second){ //Si el padre es menor, swap
              intercambia(i, Parent(i));
              Heapify_Down_to_Up(Parent(i));
              return;
        }  //Si tienen la misma prioriedad acomoda segun la clave
        if(heap[Parent(i)].second == heap[i].second)
              if(heap[Parent(i)].first < heap[i].first){
                      intercambia(i, Parent(i));
                      Heapify_Down_to_Up(Parent(i));
              }

    }
    void Heapify_Up_to_Down(ll i){ //Checa si sus hijos son mayores
        ll tam = heap.size();
        if(tam < 2*i+2) //En caso de que no tenga ningun hijo
              return;
        if(tam > 2*i+2){ //Si tiene dos hijos
              if(heap[i].second > heap[Left(i)].second && heap[i].second > heap[Right(i)].second) //Si es el mayor de los tres
                    return;
              if(heap[Left(i)].second > heap[i].second && heap[Left(i)].second > heap[Right(i)].second){ //Si el izquierdo es el mayor de los 3
                    intercambia(i, Left(i));
                    Heapify_Up_to_Down(Left(i));
                    return;
              }
              if(heap[Right(i)].second > heap[i].second && heap[Right(i)].second > heap[Left(i)].second){ //Si el derecho es el mayor de los 3
                    intercambia(i, Right(i));
                    Heapify_Up_to_Down(Right(i));
                    return;
              }
              if(heap[i].second > heap[Left(i)].second && heap[i].second == heap[Right(i)].second){ //Si es mayor que el izquierdo e igual que el otro
                    if(heap[Right(i)].first > heap[i].first){
                          intercambia(i, Right(i));
                          Heapify_Up_to_Down(Right(i));
                          return;
                    }
              }
              if(heap[i].second > heap[Right(i)].second && heap[i].second == heap[Left(i)].second){ //Si es mayor que el dercho e igual que el otro
                    if(heap[Left(i)].first > heap[i].first){
                          intercambia(i, Left(i));
                          Heapify_Up_to_Down(Left(i));
                          return;
                    }
              }
              if(heap[i].second == heap[Right(i)].second && heap[i].second == heap[Left(i)].second){ //Si todos tienen la misma prioriedad
                    if(heap[Left(i)].first > heap[Right(i)].first && heap[Left(i)].first > heap[i].first){
                          intercambia(i, Left(i));
                          Heapify_Up_to_Down(Left(i));
                          return;
                    }
                    if(heap[Right(i)].first > heap[i].first && heap[Right(i)].first > heap[i].first){
                          intercambia(i, Right(i));
                          Heapify_Up_to_Down(Right(i));
                          return;
                    }
              }

              if(heap[i].second < heap[Right(i)].second && heap[i].second < heap[Left(i)].second && heap[Right(i)].second == heap[Left(i)].second){ //Si es menor que ambos y los otros dos son iguales
                    if(heap[Left(i)].first > heap[Right(i)].first){
                          intercambia(i, Left(i));
                          Heapify_Up_to_Down(Left(i));
                          return;
                    }
                    intercambia(i, Right(i));
                    Heapify_Up_to_Down(Right(i));
                    return;
              }

        }else{ //Si tiene solo un hijo
              if(heap[Left(i)].second < heap[i].second)
                    return;
              if(heap[Left(i)].second > heap[i].second){ //Si el hijo es mayor
                    intercambia(i, Left(i));
                    return;
              }
              if(heap[Left(i)].second == heap[i].second && heap[Left(i)].first < heap[i].first){ //Si tienen la misma prioriedad
                    intercambia(i, Left(i));
                    Heapify_Up_to_Down(Left(i));
              }
        }
    }
    void ActualizaI(ll i, T new_val){
        T aux = heap[i].second;
        heap[i].second = new_val;
        if(aux > new_val){
            Heapify_Up_to_Down(i); //Si el nuevo valor es menor, reacomoda con los hijos
            return;
        }
        if(aux < new_val){
            Heapify_Down_to_Up(i); //Si el nuevo valor es mayor, reacomoda con el padre
            return;
        }
    }

  public:
    void imprimeTodo(){
        ll tam = heap.size();
        for(ll i=0;i<tam;i++)
            if(mapa.count(heap[i].first)>0)
              cout << "index: " << mapa[heap[i].first]<< "  prioriedad: " << heap[i].second<< "  Clave: " << heap[i].first <<'\n';
    }
    void imprimeMap(){
      for (auto it = mapa.cbegin(); it != mapa.cend(); ++it) {
          std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
      }
    }

    bool emptyheap(){
        if(heap.size()==0)
            return 1;
        else
            return 0;
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
    pair<Key, T> top() const{
        return heap[0];

    }

    void insertOrUpdate(const Key k, const T p){
        if(mapa.count(k)>0){ //Si la clave ya esta, cambia el valor //mapa.count(k) nos da la cantidad de veces que esta el elemento k en el mapa.
              int aux = mapa[k] ; //Nos da la posicion del elemento en el vector
              ActualizaI(aux, p);
        }else{ //Si la clave no esta, insertala y ordena
              ll t = heap.size();
              mapa.insert(make_pair(k, t));
              heap.push_back(make_pair(k, p));
              Heapify_Down_to_Up(t);
        }
    }

    void eraseH(const Key K){//Le pasamos la clave y borra el elemento del heap.
          bool is = isInserted(K);
          if(is == 0)//Si no esta insertado, no hace nada
                return;
          if(heap.size()==1){//En caso de tener un unico elemento solo lo saca
                heap.pop_back();
                mapa.clear();
                return;
          } //En otro caso , intercambia el que se va a sacar y el ultimo, saca el ultimo, y reacomoda.
          if(mapa[K]==heap.size()-1){//Si es el ultimo, solo lo saca
                heap.pop_back();
                auto it=mapa.find(K);
                mapa.erase(it);
                return;
          }
          //Si no es el ultimo, lo intercambia con el ultimo y lo saca.
          ll aux = mapa[K];
          T aux2 = heap[aux].second;
          intercambia(mapa[K], heap.size()-1);
          heap.pop_back();
          auto it=mapa.find(K);
          mapa.erase(it);
          if(heap[aux].second >= aux2){ //Si la prioriedad del que estaba al ultimo, es mayor del que acaba de sacar, checa la relacion con su padre
                if(aux!=0)
                    Heapify_Down_to_Up(aux);
                else
                    Heapify_Up_to_Down(aux);
          }else{
                if(heap[aux].second < aux2) //Si la prioriedad del que estaba al ultimo, es menor de la prioriedad del que acab de sacar, checa la relacion con sus hijos
                    Heapify_Up_to_Down(aux);
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
  //std::cout << "heap actual despues de la accion " <<action << '\n';
  //UHeap.imprimeTodo();
  //std::cout << "mapa actual:" << '\n';
  //UHeap.imprimeMap();
  //std::cout  << '\n';
  }
  return 0;
}
