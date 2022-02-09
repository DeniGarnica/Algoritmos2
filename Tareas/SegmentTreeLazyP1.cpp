#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000

int tree[MAX] = {0}; // Para almacenar el Segment Tree
int lazy[MAX] = {0}; // Para almacenar updates pendientes

//Este es un SegmentTree con Lazzy Propagation, el cual nos da la suma de los valores de un rango dado

/* actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente
[update_l, update_r] es el intervalo que vamos a actualizar
diff: lo que se va a sumar al intervalo [update_l, update_r] */
void updateRangeUtil(int actual, int a_l, int a_r, int update_l, int update_r, int diff){
	if (lazy[actual] != 0){ //Si hay updates pendientes, los realizamos
    		tree[actual] += (a_r-a_l+1)*lazy[actual];
    		if (a_l != a_r){ //Si no es un nodo hoja
        			// Posponemos la informacion a los hijos
        			lazy[actual*2 + 1] += lazy[actual];
        			lazy[actual*2 + 2] += lazy[actual];
    		}
    		lazy[actual] = 0; //Al haber actualizado el actual, no tiene nada pendiente
	}

	if (a_l>a_r || a_l>update_l || a_r<update_l) //Si esta fuera del rango
		    return;

	//Si el rango esta completamente contenido
	if (a_l>=update_l && a_r<=update_r){
    		tree[actual] += (a_r-a_l+1)*diff; //Modificamos el nodo actual
    		if (a_l != a_r){ //Si no es nodo hoja
        			// Posponemos la informacion a los hijos
        			lazy[actual*2 + 1] += diff;
        			lazy[actual*2 + 2] += diff;
    		}
    		return;
	}

	//Si solo esta el rango parcialmente contenido, pasamos a los hijos
	int mid = (a_l+a_r)/2;
	updateRangeUtil(actual*2+1, a_l, mid, update_l, update_r, diff);
	updateRangeUtil(actual*2+2, mid+1, a_r, update_l, update_r, diff);

	//Con los hijos actualizados, calcular el resultado de estos y actualizar a este nodo.
	tree[actual] = tree[actual*2+1] + tree[actual*2+2];
}

//Actualiza el rango usando la funcion anterior
void updateRange(int n, int update_l, int update_r, int diff){
    updateRangeUtil(0, 0, n-1, update_l, update_r, diff);
}


/* A recursive function to get the sum of values in given
	range of the array. The following are parameters for
	this function.
	si --> Index of current node in the segment tree.
		Initially 0 is passed as root is always at'
		index 0
	ss & se --> Starting and ending indexes of the
				segment represented by current node,
				i.e., tree[si]
	qs & qe --> Starting and ending indexes of query
				range */
int getSumUtil(int ss, int se, int qs, int qe, int si)
{
	// If lazy flag is set for current node of segment tree,
	// then there are some pending updates. So we need to
	// make sure that the pending updates are done before
	// processing the sub sum query
	if (lazy[si] != 0)
	{
		// Make pending updates to this node. Note that this
		// node represents sum of elements in arr[ss..se] and
		// all these elements must be increased by lazy[si]
		tree[si] += (se-ss+1)*lazy[si];

		// checking if it is not leaf node because if
		// it is leaf node then we cannot go further
		if (ss != se)
		{
			// Since we are not yet updating children os si,
			// we need to set lazy values for the children
			lazy[si*2+1] += lazy[si];
			lazy[si*2+2] += lazy[si];
		}

		// unset the lazy value for current node as it has
		// been updated
		lazy[si] = 0;
	}

	// Out of range
	if (ss>se || ss>qe || se<qs)
		return 0;

	// At this point we are sure that pending lazy updates
	// are done for current node. So we can return value
	// (same as it was for query in our previous post)

	// If this segment lies in range
	if (ss>=qs && se<=qe)
		return tree[si];

	// If a part of this segment overlaps with the given
	// range
	int mid = (ss + se)/2;
	return getSumUtil(ss, mid, qs, qe, 2*si+1) +
		getSumUtil(mid+1, se, qs, qe, 2*si+2);
}

// Return sum of elements in range from index qs (query
// start) to qe (query end). It mainly uses getSumUtil()
int getSum(int n, int qs, int qe){
	// Check for erroneous input values
	if (qs < 0 || qe > n-1 || qs > qe)
	{
		printf("Invalid Input");
		return -1;
	}

	return getSumUtil(0, n-1, qs, qe, 0);
}

// Construye el ST dado un arreglo, un intervalo y el indice del nodo actual
void constructSTUtil(int arr[], int a_l, int a_r, int actual){
	// out of range as ss can never be greater than se
	if (a_l > a_r) //Si se sale del rango
		return ;

  //Si el intervalo es de tamanio 1, acomoda las hojas
	if (a_l == a_r){
		tree[actua] = int(arr[a_l]);
		return;
	}

	// Si es de tamanio mayor a uno, va a los hijos
	int mid = (a_l + a_r)/2;
	constructSTUtil(arr, a_l, mid, actual*2+1);
	constructSTUtil(arr, mid+1, a_r, actual*2+2);

	tree[actual] = tree[actual*2 + 1] + tree[actual*2 + 2];
}

//Construye todo el ST usando la funcion anterior
void constructST(int arr[], int n){
	constructSTUtil(arr, 0, n-1, 0);
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

      int num_operaciones;
      std::cin >> num_operaciones;

      for (int j = 0; j < num_operaciones; j++) {
          char operacion;
          std::cin >> operacion;
          int l, r;
          std::cin >> l >> r;
          if(operacion == 'F'){

          }

          if(operacion == 'E'){

          }

          if(operacion == 'I'){

          }

          if(operacion == 'S'){

          }
      }
  }
	return 0;
}
