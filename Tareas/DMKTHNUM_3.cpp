#include <iostream>
#include <cmath>
#include <vector>

struct _Node{
  int x, cnt;
  long long p;
  _Node *l, *r;
  _Node (int v): x(v), p(((long long)(rand())<<32)^rand()), cnt(1), l(NULL), r(NULL) {}
  ~_Node() {delete l; delete r;}
  void recalc(){
    cnt = 1;
    cnt += ((l)?(l->cnt):0);
    cnt += ((r)?(r->cnt):0);

  }
}; typedef _Node *Node;

Node merge(Node l, Node r){ //Se asume que los arboles que nos pasan estan bien acomodados
  if(!l || !r) return l? l:r;
  if(l->p > r->p){
    l->r = merge(l->r, r);
    l->recalc();
    return l;
  }else{
    r->l = merge(l, r->l);
    r->recalc();
    return r;
  }
}

void SplitByValue(Node n, int d, Node &l, Node &r){ //En l quedan los menores a d, en r quedan los mayores iguales a d.
  if(!n){ //Si el nodo esta vacio
    l = r = NULL;
    return;
  }
  l = r = NULL;
  if(n->x <d){
    SplitByValue(n->r, d, n->r, r);
    l=n;
  }else{
    SplitByValue(n->l, d, l, n->l);
    r=n;
  }
  n->recalc();
}

int less_equal_k(Node root, int k){ //Nos de la cantidad de nodos con valor menor igual a k
    if(root==NULL)
      return 0;
    if(root->x <= k){
      if(root->l!=NULL)
        return root->l->cnt + 1 + less_equal_k(root->r, k);
      else
        return 1 + less_equal_k(root->r, k);
    }else{
      return less_equal_k(root->l, k);
    }
}

//Todo lo necesario en un Segment Tree
#define MAX 1000005
Node tree[4*MAX]; // Para almacenar el Segment Tree
int valores[MAX]; //Guarda los valores del arrwglo

//En este SegmentTree cada nodo tiene un treap, este treap contiene un conjunto de indices

//Usando las funciones del treap elimina un valor especifico
void actualiza_conjunto_borra(Node &conjunto, int quitar){
    Node l = NULL;
    Node r = NULL;
    //Quitamos el valor que no nos interesa
    SplitByValue(conjunto, quitar, l, r);
    Node l_2 = NULL;
    Node r_2 = NULL;
    SplitByValue(r, quitar+1, l_2, r_2);
    conjunto =  merge(l, r_2);
}

//Usando las funciones del treap agrega un conjunto
void actualiza_conjunto_agrega(Node &conjunto, int agregar){

    Node n0 = new _Node(agregar);
    Node l_2 = NULL;
    Node r_2 = NULL;
    //Agregamos el que nos interesa separando los menores y los mayores iguales a el
    SplitByValue(conjunto, agregar, l_2, r_2);

    conjunto =  merge(l_2, merge(n0, r_2));
}

/* actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente
[update_l, update_r] es el intervalo que vamos a actualizar, este caso update_l == update_r = valor
cambio: la operacion que se va a realizar al intervalo [update_l, update_r], en este caso agregar o eliminra el indice
action: nos dice 0 si debemos borrar el elemento y 1 si lo vamos a agregar */
void updateRangeUtil(int actual, int a_l, int a_r, int update_l, int update_r, int cambio, bool action){
    if (a_l>a_r || a_l>update_r || a_r<update_l) //Si esta fuera del rango
            return;

    if(!action)
        actualiza_conjunto_borra(tree[actual], cambio);
    else
        actualiza_conjunto_agrega(tree[actual], cambio);
    //Si llegamos a la hoja no es necesario hacer nada mas
    if (a_l == a_r)
      return;
    //Si aun no estamos en una hoja, vamos hacia los hijos
    int mid = (a_l+a_r)/2;
    updateRangeUtil(actual*2+1, a_l, mid, update_l, update_r, cambio, action);
    updateRangeUtil(actual*2+2, mid+1, a_r, update_l, update_r, cambio, action);

}

//Actualiza el rango usando la funcion anterior
void updateRange(int n, int update_l, int update_r, int cambio, bool action){

    updateRangeUtil(0, 0, n-1, update_l, update_r, cambio, action);
}

//Realiza las actualizaciones
void cambia_valor(int indice, int valor_nuevo){
    int anterior = valores[indice];
    //Quitamos el indice del valor anterior
    updateRange(MAX, anterior, anterior, indice, 0); //0 = borrar
    //Agregamos el indice del valor nuevo
    updateRange(MAX, valor_nuevo, valor_nuevo, indice, 1); //1 = agregar

    //Actualizamos el arreglo que conserva los valores
    valores[indice] = valor_nuevo;
}

int num_utiles(Node actual, int a_l, int a_r){
    //Nos da la cantidad de indices que nos sirven dependiendo del intervalo que buscamos
    return less_equal_k(actual, a_r) - less_equal_k(actual, a_l-1);
}

/*Nos da la cantidad de unos en un intervalo
actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente, ie tree[actual]
[update_l, update_r] es el intervalo del query
cambio: la operacion que se va a realizar al intervalo [update_l, update_r]*/
int query_Util(int a_l, int a_r, int q_l, int q_r, int actual, int k){

    // Si ya llegamos a la hoja
    if (a_l == a_r)
        return a_l;

    //Si no estamos en una hoja vemos la cantidad de indices que nos importan
    int en_izq = num_utiles(tree[actual*2+1], q_l, q_r);
    int mid = (a_l + a_r)/2;

    // decidimos si ir a la izquierda o a la derecha
    if(en_izq >= k + 1)
      return query_Util(a_l, mid, q_l, q_r, 2*actual+1, k);
    else
      return query_Util(mid+1, a_r, q_l, q_r, 2*actual+2, k-en_izq);

}

int query(int n, int q_l, int q_r, int k){
    return query_Util(0, n-1, q_l, q_r, 0, k);
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n, n_q, q, l, r, k, val;
  std::cin >> n;
  for (int i = 0; i < n; i++){
    std::cin >> valores[i];
    updateRange(MAX, valores[i], valores[i], i, 1); //Agregamos el indice al valor
  }


  std::cin >> n_q;
  for (int i = 0; i < n_q; i++) {
    std::cin >> q;
    if(q == 0){
      std::cin >> l >> r >> k;
      int res = query(MAX, l, r, k);
      std::cout << res << '\n';
    }
    if(q == 1){
      std::cin >> k >> val;
      cambia_valor(k, val);
    }
  }
  return 0;
}
