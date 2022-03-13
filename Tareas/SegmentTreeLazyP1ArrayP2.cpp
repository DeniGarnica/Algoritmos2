#include <iostream>
using namespace std;
#define ll long long
#define MAX 1000000

int tree[4*MAX]; // Para almacenar el Segment Tree, guarda la suma_actumulada
int lazy[4*MAX]; // Para almacenar updates pendientes, existen 3 tipos de update
//Este es un SegmentTree con Lazzy Propagation, el cual nos da la suma de los valores de un rango dado
//Esta funcion actualiza el intervalo suponiendo que esta completamente contenido.

int prefijo[4*MAX][2]; //Guarda el min_prefijo, max_prefijo

//+1 = (, -1 =), 0 = letra
int update(int a_l, int a_r , int actual, int cambio){ //Actualizar el valor del rango en el tree
  if(a_r-a_l+1 == 1){ //Si estamos en la hoja solo movemos los valores
    prefijo[actual][0] = cambio;
    prefijo[actual][1] = cambio;
    return cambio;
  }
    //Como siempre va a expandirse hasta la hoja primero, podemos ver que las hojas se actualizan antes que sus padres
    prefijo[actual][0] = min(prefijo[actual*2+1][0], prefijo[actual*2+2][0] + tree[actual*2+1]);
    prefijo[actual][1] = max(prefijo[actual*2+1][0], prefijo[actual*2+2][0] + tree[actual*2+1]);
    return tree[actual] + cambio; //Al cambiar una hoja la suma se conserva excepto por el que se cambio

}

int combinar_updates(int cambio_n, int  lazy_actual){
  return cambio_n;
}

int juntar_tree(int izq, int der){
  prefijo[int((izq-1)/2)][0] = min(prefijo[izq][0], prefijo[der][0] + tree[izq]);
  prefijo[int((der-2)/2)][1] = max(prefijo[izq][1], prefijo[der][1] + tree[izq]);
  return tree[der] + tree[izq]; //Modificamos la suma acumulada
}

/*Nos da la cantidad de unos en un intervalo
actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente, ie tree[actual]
[update_l, update_r] es el intervalo del query
cambio: la operacion que se va a realizar al intervalo [update_l, update_r]*/
int getSumUtil(int a_l, int a_r, int q_l, int q_r, int actual){
    if (lazy[actual] != 0){ //Si hay updates pendientes los realiza
        tree[actual] = update(a_r, a_l, actual, lazy[actual]);

        if (a_l != a_r){ //Si no es un nodo hoja
      //Posponemos a los hijos
            lazy[actual*2+1] = combinar_updates(lazy[actual], lazy[actual*2 + 1]);
            lazy[actual*2+2] = combinar_updates(lazy[actual], lazy[actual*2 + 2]);
        }

        lazy[actual] = 0; //Al haber actualizado el actual, no tiene nada pendiente
    }

    if (a_l>a_r || a_l>q_r || a_r<q_l) //Si esta fuera del rango
        return 0;

    // Si el rango esta contenido
    if (a_l>=q_l && a_r<=q_r)
        return tree[actual];

    // Si no todo el rango esta contenido
    int mid = (a_l + a_r)/2;
    return getSumUtil(a_l, mid, q_l, min(q_r, mid), 2*actual+1) + getSumUtil(mid+1, a_r, max(q_l, mid+1), q_r, 2*actual+2);
}

int getSum(int n, int q_l, int q_r){
    return getSumUtil(0, n-1, q_l, q_r, 0);
}

/* actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente
[update_l, update_r] es el intervalo que vamos a actualizar
cambio: la operacion que se va a realizar al intervalo [update_l, update_r] */
void updateRangeUtil(int actual, int a_l, int a_r, int update_l, int update_r, int cambio, int old){
    if (lazy[actual] != 0){ //Si hay updates pendientes, los realizamos
            tree[actual] = update(a_r, a_l, actual, cambio) - old;
            if (a_l != a_r){ //Si no es un nodo hoja
                    // Posponemos la informacion a los hijos combinando lo nuevo que se paso con lo que ya tenia
                    lazy[actual*2 + 1] = combinar_updates(lazy[actual], lazy[actual*2 + 1]);
                    lazy[actual*2 + 2] = combinar_updates(lazy[actual], lazy[actual*2 + 2]);
            }
            lazy[actual] = 0; //Al haber actualizado el actual, no tiene nada pendiente
    }

    if (a_l>a_r || a_l>update_r || a_r<update_l) //Si esta fuera del rango
            return;

    //Si el rango actual esta completamente contenido en el que queremos actualizar
    if (a_l>=update_l && a_r<=update_r){
            tree[actual] = update(a_r, a_l, actual, cambio, old); //Modificamos el nodo actual
            if (a_l != a_r){ //Si no es nodo hoja
                    // Posponemos la informacion a los hijos
                    lazy[actual*2 + 1] = combinar_updates(cambio, lazy[actual*2 + 1]);
                    lazy[actual*2 + 2] = combinar_updates(cambio, lazy[actual*2 + 2]);
            }
            return;
    }

    //Si solo esta el rango parcialmente contenido, pasamos a los hijos
    int mid = (a_l+a_r)/2;
  //std::cout << "se paso a los rangos: ["<<a_l<<", "<<mid<<"] y ["<<mid+1<<", "<<a_r<<"]" << '\n';
    updateRangeUtil(actual*2+1, a_l, mid, update_l, update_r, cambio);
    updateRangeUtil(actual*2+2, mid+1, a_r, update_l, update_r, cambio);

    //Con los hijos actualizados, calcular el resultado de estos y actualizar a este nodo.
    tree[actual] = juntar_tree(actual*2+1, actual*2+2);
}

//Actualiza el rango usando la funcion anterior
void updateRange(int n, int update_l, int update_r, int cambio){
    int old = getSum(n, update_l, update_r);
    updateRangeUtil(0, 0, n-1, update_l, update_r, cambio, old);
}


// Construye el ST dado un arreglo, un intervalo y el indice del nodo actual
void constructSTUtil(const string &arr, int a_l, int a_r, int actual){
    // out of range as ss can never be greater than se
    lazy[actual] = 0;

    if (a_l > a_r) //Si se sale del rango
        return;

  //Si el intervalo es de tamanio 1, acomoda las hojas
    if (a_l == a_r){
      if(arr[actual] == '('){
          prefijo[actual][0] = 1;
          prefijo[actual][1] = 1;
          tree[actual] = 1;
          return;
      }
      if(arr[actual] == ')'){
          prefijo[actual][0] = -1;
          prefijo[actual][1] = -1;
          tree[actual] = -1;
          return;
      }

      prefijo[actual][0] = 0;
      prefijo[actual][1] = 0;
      tree[actual] = 0;
      return;
    }

    // Si es de tamanio mayor a uno, va a los hijos
    int mid = (a_l + a_r)/2;
    constructSTUtil(arr, a_l, mid, actual*2+1);
    constructSTUtil(arr, mid+1, a_r, actual*2+2);

    tree[actual] = juntar_tree(actual*2+1, actual*2+2);
}

//Construye todo el ST usando la funcion anterior
void constructST(string arr, int n){
    constructSTUtil(arr, 0, n-1, 0);
}

void checar(){
  if (tree[0] == 0 && prefijo[0][0] == 0){
    std::cout << 1 << '\n';
    std::cout << prefijo[0][1] << '\n';
  }else{
    std::cout << -1 << '\n';
  }
  return;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_casos;
  std::cin >> num_casos;
  char cadena[num_casos];
  constructST(cadena, num_casos);
  char aux;
  int actual = 0;
  int n = 0;
  for(int i = 0; i < num_casos; i++){
      std::cin >> aux;
      if(aux == 'R' && actual < num_casos)
        actual++;
      if(aux == 'L' &&  actual>0 )
        actual--;
      if(aux != 'L' && aux != 'R'){
        n++;
        if(aux == '('){
          cadena[actual] = 1;
            updateRange(num_casos, actual, actual, 1);

          }
        if(aux == ')'){
            cadena[actual] = -1;
            updateRange(num_casos, actual, actual, -1);
          }
        if(aux != ')' && aux != '('){
            cadena[actual] = 0;
            updateRange(num_casos, actual, actual, 0);
        }
      }
      checar();
  }
    return 0;
}
