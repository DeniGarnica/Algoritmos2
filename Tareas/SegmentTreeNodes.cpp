#include <iostream>
#include <cmath>
#include <vector>
#define ll long long
#define MAX 1000000

struct _Node{
  long long x, cnt;
  long long p;
  _Node *l, *r;
  _Node (int v): x(v), cnt(1), l(NULL), r(NULL) {}
  ~_Node() {delete l; delete r;}
  void recalc(){
    cnt = 1;
    cnt += ((l)?(l->cnt):0);
    cnt += ((r)?(r->cnt):0);
  }
}; typedef _Node *Node;

void printArbol(Node a, int con){
  if(a==NULL){
    return;
  }else{
    printArbol(a->r, con+1);
    for(int i=0; i<con;i++)
      std::cout << " ";
    std::cout << a->x << '\n';
    //std::cout << a->x <<", "<<a->cnt<<'\n';
    //std::cout << a->x <<", "<<a->cnt<< ", p: "<<a->p<<'\n';
    printArbol(a->l, con+1);
  }
}

int juntar_tree(Node l, Node r){
    return (l->x + r->x);
}

//Esta funcion actualiza el intervalo suponiendo que esta completamente contenido.
int update(int a_l, int a_r, int cambio, Node actual){
  return 1;
}

// Construye el ST dado un arreglo, un intervalo y el indice del nodo actual
// [a_l, a_r]: rango que se esta construyendo
void constructSTUtil(int *arr, int a_l, int a_r, Node actual){

    if (a_l > a_r) //Si se sale del rango
        return ;

  //Si el intervalo es de tamanio 1, acomoda las hojas
    if (a_l == a_r){
        actual->x = arr[a_l];
    //std::cout << "tree["<<a_l<< "]: "<< tree[actual] << '\n';
        return;
    }

    // Si es de tamanio mayor a uno, va a los hijos
    int mid = (a_l + a_r)/2;
    constructSTUtil(arr, a_l, mid, actual->l);
    constructSTUtil(arr, mid+1, a_r, actual->r);

    actual->x = juntar_tree(actual->l, actual->r);
}

//Construye todo el ST usando la funcion anterior
void constructST(int *arr, int n){
    constructSTUtil(arr, 0, n-1, 0);
}

int get_query_Util(int a_l, int a_r, int q_l, int q_r, Node actual){

    if (a_l>a_r || a_l>q_r || a_r<q_l) //Si esta fuera del rango
        return 0;

    // Si el rango esta contenido
    if (a_l>=q_l && a_r<=q_r)
        return actual->x;

    // Si no todo el rango esta contenido
    int mid = (a_l + a_r)/2;
    return juntar_tree(get_query_Util(a_l, mid, q_l, q_r, actual->l), getSumUtil(mid+1, a_r, q_l, q_r, actual->r));
}

int get_query(Node root, int q_l, int q_r){

    return getSumUtil(0, n-1, q_l, q_r, root);
}

/* actual: nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente
[update_l, update_r] es el intervalo que vamos a actualizar
cambio: la operacion que se va a realizar al intervalo [update_l, update_r] */
void updateRangeUtil(Node actual, int a_l, int a_r, int update_l, int update_r, int cambio){
    if (a_l>a_r || a_l>update_r || a_r<update_l) //Si esta fuera del rango
            return;

    //Si el rango actual esta completamente contenido en el que queremos actualizar
    if (a_l>=update_l && a_r<=update_r){
            actual->x = update(a_l, a_r, cambio, actual); //Modificamos el nodo actual
            return;
    }

    //Si solo esta el rango parcialmente contenido, pasamos a los hijos
    int mid = (a_l+a_r)/2;

    updateRangeUtil(actual->l, a_l, mid, update_l, update_r, cambio);
    updateRangeUtil(actual->r, mid+1, a_r, update_l, update_r, cambio);

    //Con los hijos actualizados, calcular el resultado de estos y actualizar a este nodo.
    actual->x = juntar_tree(actual->l, actual->r);
}

//Actualiza el rango usando la funcion anterior
void updateRange(Node root, int update_l, int update_r, int cambio){
    updateRangeUtil(root, 0, n-1, update_l, update_r, cambio);
}
