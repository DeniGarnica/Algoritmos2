#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100000

int tree[MAX] = {0}; // Para almacenar el Segment Tree
int lazy[MAX] = {0}; // Para almacenar updates pendientes, existen 3 tipos de update

//Este es un SegmentTree con Lazzy Propagation, el cual nos da la suma de los valores de un rango dado
//Esta funcion actualiza el intervalo suponiendo que esta completamente contenido.
int update(int rango_size, int cambio, int v_actual){

  if(cambio == 3) //Si cambio == 3, cambia todos los del rango a 0
      return 0;

  if(cambio == 1) //Si cambio == 1, cambia a todos los del rango a 1
      return rango_size;

  if(cambio == 2) //Si cambio == 2, intercambia los valores
      return rango_size - v_actual;
}

int combinar_updates(int cambio_n, int  lazy_actual){
 //Solo nos importa el anterior si el nuevo es un intercambio
  if(lazy_actual == 2 && cambio_n == 2) //Si nos pide intercambiar valores 2 veces, es lo mismo a no tener nada pendiente
      return 0;

  if(lazy_actual == 1 && cambio_n == 2) //Si nos pide intercambiar y previamente nos pedia estar en 1
      return 3;

  if(lazy_actual == 3 && cambio_n == 2) //Si nos pide intercambiar y previamente nos pedia estar en 3
      return 1;
  //Si el nuevo no es un intercambio solo ponemos el mismo numero
  return cambio_n; //Si nos pide cambiar a otro numero, solo lo hacemos
}


/* actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente
[update_l, update_r] es el intervalo que vamos a actualizar
cambio: la operacion que se va a realizar al intervalo [update_l, update_r] */
void updateRangeUtil(int actual, int a_l, int a_r, int update_l, int update_r, int cambio){
	if (lazy[actual] != 0){ //Si hay updates pendientes, los realizamos
    		tree[actual] = update(a_r-a_l+1, lazy[actual], tree[actual]);
    		if (a_l != a_r){ //Si no es un nodo hoja
        			// Posponemos la informacion a los hijos combinando lo nuevo que se paso con lo que ya tenia
        			lazy[actual*2 + 1] = combinar_updates(lazy[actual], lazy[actual*2 + 1]);
        			lazy[actual*2 + 2] = combinar_updates(lazy[actual], lazy[actual*2 + 2]);
    		}
    		lazy[actual] = 0; //Al haber actualizado el actual, no tiene nada pendiente
	}

	if (a_l>a_r || a_l>update_l || a_r<update_l) //Si esta fuera del rango
		    return;

	//Si el rango esta completamente contenido
	if (a_l>=update_l && a_r<=update_r){
    		tree[actual] = update(a_r-a_l+1, cambio, tree[actual]); //Modificamos el nodo actual
    		if (a_l != a_r){ //Si no es nodo hoja
        			// Posponemos la informacion a los hijos
        			lazy[actual*2 + 1] = combinar_updates(cambio, lazy[actual*2 + 1]);
        			lazy[actual*2 + 2] = combinar_updates(cambio, lazy[actual*2 + 2]);
    		}
    		return;
	}

	//Si solo esta el rango parcialmente contenido, pasamos a los hijos
	int mid = (a_l+a_r)/2;
	updateRangeUtil(actual*2+1, a_l, mid, update_l, update_r, cambio);
	updateRangeUtil(actual*2+2, mid+1, a_r, update_l, update_r, cambio);

	//Con los hijos actualizados, calcular el resultado de estos y actualizar a este nodo.
	tree[actual] = tree[actual*2+1] + tree[actual*2+2];
}

//Actualiza el rango usando la funcion anterior
void updateRange(int n, int update_l, int update_r, int cambio){
    updateRangeUtil(0, 0, n-1, update_l, update_r, cambio);
}


/* Nos da la cantidad de unos en un intervalo
actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente, ie tree[actual]
[update_l, update_r] es el intervalo del query
cambio: la operacion que se va a realizar al intervalo [update_l, update_r] */
int getSumUtil(int a_l, int a_r, int q_l, int q_r, int actual){
	if (lazy[actual] != 0){ //Si hay updates pendientes los realiza
		tree[actual] = update(a_r-a_l+1, lazy[actual], tree[actual]);

		if (a_l != a_r){ //Si no es un nodo hoja
      //Posponemos a los hijos
			lazy[actual*2+1] = combinar_updates(lazy[actual], lazy[actual*2 + 1]);
			lazy[actual*2+2] = combinar_updates(lazy[actual], lazy[actual*2 + 2]);
		}

		lazy[actual] = 0; //Al haber actualizado el actual, no tiene nada pendiente
	}

	if (a_l>a_r || a_r>q_r || a_r<q_l) //Si esta fuera del rango
		return 0;

	// Si el rango esta contenido
	if (a_l>=q_l && a_r<=q_r)
		return tree[actual];

	// Si no todo el rango esta contenido
	int mid = (a_l + a_r)/2;
	return getSumUtil(a_l, mid, q_l, q_r, 2*actual+1) + getSumUtil(mid+1, a_r, q_l, q_r, 2*actual+2);
}


int getSum(int n, int q_l, int q_r){
	// Revisa errores
	if (q_l < 0 || q_r > n-1 || q_l > q_r){
		printf("Invalid Input");
		return -1;
	}

	return getSumUtil(0, n-1, q_l, q_r, 0);
}

// Construye el ST dado un arreglo, un intervalo y el indice del nodo actual
void constructSTUtil(string arr, int a_l, int a_r, int actual){
	// out of range as ss can never be greater than se
	if (a_l > a_r) //Si se sale del rango
		return ;

  //Si el intervalo es de tamanio 1, acomoda las hojas
	if (a_l == a_r){
		tree[actual] = int(arr[a_l])-int('0');
    //std::cout << "tree["<<a_l<< "]: "<< tree[actual] << '\n';
		return;
	}

	// Si es de tamanio mayor a uno, va a los hijos
	int mid = (a_l + a_r)/2;
	constructSTUtil(arr, a_l, mid, actual*2+1);
	constructSTUtil(arr, mid+1, a_r, actual*2+2);

	tree[actual] = tree[actual*2 + 1] + tree[actual*2 + 2];
}

//Construye todo el ST usando la funcion anterior
void constructST(string arr, int n){
	constructSTUtil(arr, 0, n-1, 0);
}

void imprime(){
  std::cout << tree[0] << '\n';
  std::cout << tree[1]<<" "<<tree[2] << '\n';
  for (int i = 0; i < 4; i++)
    std::cout << tree[3+i] << " ";
  std::cout  << '\n';
//  for (int i = 0; i < 8; i++)
  //  std::cout << tree[7+i] << " ";
//  std::cout  << '\n';
}

void imprimeLazy(){
  std::cout << lazy[0] << '\n';
  std::cout << lazy[1]<<" "<<lazy[2] << '\n';
  for (int i = 0; i < 4; i++)
    std::cout << lazy[3+i] << " ";
  std::cout  << '\n';
//  for (int i = 0; i < 8; i++)
//    std::cout << lazy[7+i] << " ";
  //std::cout  << '\n';
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int num_casos;
  std::cin >> num_casos;
  for(int i = 0; i < num_casos; i++){
      string cadena, sub_cadena;
      int num_subcadenas;
      std::cin >> num_subcadenas;
      for (int j = 0; j < num_subcadenas; j++){
        int sub_size;
        std::cin >> sub_size;
        std::cin >> sub_cadena;
        for (int k = 0; k <sub_size ; k++) {
          cadena += sub_cadena;
        }
      }
      int n = cadena.length();
      constructST(cadena, n);
      std::cout << "inicial" << '\n';
      imprime();

      /*for (int k = 0; k < 10; k++) {
        std::cout << "tree: "<< tree[k] << '\n';
      }*/

      int num_operaciones;
      std::cin >> num_operaciones;

      for (int j = 0; j < num_operaciones; j++) {
          char operacion;
          std::cin >> operacion;
          int l, r;
          std::cin >> l >> r;
          if(operacion == 'F'){
              updateRange(n, l, r, 1);
              std::cout << "tree F" << '\n';
              imprime();
              std::cout << "Lazy" << '\n';
              imprimeLazy();
            }

          if(operacion == 'E'){
              updateRange(n, l, r, 3);
              std::cout << "tree E" << '\n';
              imprime();
              std::cout << "Lazy" << '\n';
              imprimeLazy();
            }

          if(operacion == 'I'){
              updateRange(n, l, r, 2);
              std::cout << "tree I" << '\n';
              imprime();
              std::cout << "Lazy" << '\n';
              imprimeLazy();
            }

          if(operacion == 'S'){
              std::cout << getSum(n, l, r) << '\n';
              std::cout << "tree S" << '\n';
              imprime();
              std::cout << "Lazy" << '\n';
              imprimeLazy();
            }

      }
  }
	return 0;
}
