#include <iostream>
#include <cmath>
#include <vector>
#define ll long long
#define MAX 100000

ll pesos[MAX]; //Pesos del nodo
ll altura[MAX]; //La altura de cada nodo
ll pos_camino[MAX]; //Posiciones en el camino deonde se encuentran
ll valor[MAX]; //Los valores de todos los nodos
std::vector<ll> hijos[MAX]; //Lista de sus hijos
struct camino{ //Estructura de un camino del HL
	ll pos_padre; //el nodo del que sale el camino
	ll pos_inicio; // el de hasta arriba del camino
	ll pos_fin; // el de hasta abajo del camino
	std::vector<ll> camino_valores; //Nos dice los volres en el camino en orden arriba a abajo
	std::vector<ll> SegmentTree; //Segment tree de cada camino
	ll tam;
	camino(ll padre, ll inicial){
  //Recibe cual es el nodo padre, y el nodo inicial del camino. Inicializa el camino vacio
		pos_padre = padre;
		pos_inicio = inicial;
		pos_fin = inicial; //Por ahora el inicio y el fin son el mismo
		tam = 0;
	}
	void agrega(ll nodo){ //Agrega un nodo al camino, recibiendo la posicion de este
		pos_fin = nodo;
		tam++;
		camino_valores.push_back(valor[nodo]);
	}
	void constructSTUtil(ll a_l, ll a_r, ll actual){ //Genera el segment Tree del camino

    if (a_l > a_r) //Si se sale del rango
        return ;

  //Si el intervalo es de tamanio 1, acomoda las hojas
    if (a_l == a_r){
        SegmentTree[actual] = camino_valores[a_l];
        return;
    }

		ll mid = (a_l + a_r)/2;
    constructSTUtil(a_l, mid, actual*2+1);
    constructSTUtil(mid+1, a_r, actual*2+2);

    SegmentTree[actual] = SegmentTree[actual*2+1] + SegmentTree[actual*2+2];
		return;
	}

  void constructST(){ //Genera el segment tree desde la raiz
    SegmentTree.resize(8*tam);
    constructSTUtil(0, tam-1, 0);
  }

  /* actual: inidice del nodo actual  en el segment tree
  [a_l, a_r]: es el intervalo en el que nos encontramos actualmente
  [update_l, update_r] es el intervalo que vamos a actualizar
  cambio: la operacion que se va a realizar al intervalo [update_l, update_r] */
  void updateRangeUtil(ll actual, ll a_l, ll a_r, ll update_l, ll update_r, ll cambio){ //Actualiza el Segment tree
    if (a_l>a_r || a_l>update_r || a_r<update_l) //Si esta fuera del rango
            return;

    //Si el rango actual esta completamente contenido en el que queremos actualizar
    if (a_l==a_r){
            SegmentTree[actual] = cambio; //Modificamos el nodo actual
            return;
    }

    //Si solo esta el rango parcialmente contenido, pasamos a los hijos
    ll mid = (a_l+a_r)/2;
    updateRangeUtil(actual*2+1, a_l, mid, update_l, update_r, cambio);
    updateRangeUtil(actual*2+2, mid+1, a_r, update_l, update_r, cambio);

    //Con los hijos actualizados, calcular el resultado de estos y actualizar a este nodo.
    SegmentTree[actual] = SegmentTree[actual*2+1] + SegmentTree[actual*2+2];

  }

  void updateRange(ll n, ll pos, ll cambio){
    updateRangeUtil(0, 0, n, pos, pos, cambio);
  }

  /*Nos da la cantidad de unos en un intervalo
actual: inidice del nodo actual  en el segment tree
[a_l, a_r]: es el intervalo en el que nos encontramos actualmente, ie tree[actual]
[update_l, update_r] es el intervalo del query
cambio: la operacion que se va a realizar al intervalo [update_l, update_r]*/
  ll QueryUtil(ll a_l, ll a_r, ll q_l, ll q_r, ll actual){

      if (a_l>a_r || a_l>q_r || a_r<q_l) //Si esta fuera del rango
          return 0;

      // Si el rango esta contenido
      if (a_l>=q_l && a_r<=q_r)
          return SegmentTree[actual];

      // Si no todo el rango esta contenido
      ll mid = (a_l + a_r)/2;
      return QueryUtil(a_l, mid, q_l, q_r, 2*actual+1) + QueryUtil(mid+1, a_r, q_l, q_r, 2*actual+2);
  }

  ll Query(ll n, ll q_l, ll q_r){

      return QueryUtil(0, tam-1, q_l, q_r, 0);
  }
};

camino* dirrecion_camino[MAX]; //Apuntadores a los caminos donde se encuentran

void calcula_pesos(ll pos){
  //Calcula los pesos del arbol
	pesos[pos] = 1; //Pesa al menos si mismo
	for(ll i = 0; i < hijos[pos].size(); i++){
  		altura[hijos[pos][i]] = altura[pos] + 1; //Recalculamos la altura de cada nodo respecto a la de sus hijos
  		calcula_pesos(hijos[pos][i]); //Calcula recursivamente
  		pesos[pos] += pesos[hijos[pos][i]]; //El peso depende del peso de los hijos
	}
	return;
}

void crea_caminos(ll pos){
	//Genera el arbol completo y divide en los caminos
	dirrecion_camino[pos]->agrega(pos); //Agregamos la posicion actual a su camino

	if(hijos[pos].size() == 0){
      //Si ya no hay mas indices abajo, genera el segment tree del camino
  		dirrecion_camino[pos]->constructST();
  		return;
	}
	ll mayor_peso = 0;
	for(ll i = 0; i < hijos[pos].size(); i++)
		  mayor_peso = std::max(mayor_peso, pesos[hijos[pos][i]]); //Vemos cual es el hijo mas pesado

	bool en_camino = false;

	for(ll i = 0; i < hijos[pos].size(); i++){
  		if(mayor_peso == pesos[hijos[pos][i]] && !en_camino){
      //Si estamos en el hijo mas pesado y aun no lo hemos puesto en un camino
      			pos_camino[hijos[pos][i]] = pos_camino[pos]+1; //La posicion en el camino del hijo es la del padre +1
      			dirrecion_camino[hijos[pos][i]] = dirrecion_camino[pos]; //Indicamos en que camino esta el hijo
      			crea_caminos(hijos[pos][i]); //Continuamos creando los caminos con el hijo
      			en_camino = true;
  		}else{
      			//Si no es el hijo mas pesado
      			pos_camino[hijos[pos][i]] = 0; //Es el primero del nuevo camion
      			dirrecion_camino[hijos[pos][i]] = new camino(pos, hijos[pos][i]); //Creamos un nuevo camino con este hijo
      			crea_caminos(hijos[pos][i]);
  		}
	}
}

ll suma(ll A, ll B){

	if(altura[A]<altura[B]) //Ponemos el de mayor altura en la 1a posicion
		  return suma(B,A);
  //Query(ll n, ll q_l, ll q_r)
	if(dirrecion_camino[A] != dirrecion_camino[B]){
  //Si no estan en el mismo camino
    		if(dirrecion_camino[A]->pos_padre == -1) //Si el camino de A tiene a la raiz
    			   return suma(A, dirrecion_camino[B]->pos_padre) + dirrecion_camino[B]->Query(dirrecion_camino[B]->tam-1, 0, pos_camino[B]);

        if(dirrecion_camino[B]->pos_padre == -1) //Si el camino de B tiene a la raiz
    			   return suma(dirrecion_camino[A]->pos_padre, B) + dirrecion_camino[A]->Query(dirrecion_camino[A]->tam-1, 0, pos_camino[A]);

        if(altura[dirrecion_camino[A]->pos_padre] < altura[dirrecion_camino[B]->pos_padre])
    				 return suma(A, dirrecion_camino[B]->pos_padre) + dirrecion_camino[B]->Query(dirrecion_camino[B]->tam-1, 0, pos_camino[B]);

        return suma(dirrecion_camino[A]->pos_padre, B) + dirrecion_camino[A]->Query(dirrecion_camino[A]->tam-1, 0, pos_camino[A]);

  }else{
        //Si estan en el mismo camino, solo necesitamos hacer la query en su correspondiente Segment tree
      	return dirrecion_camino[A]->Query(dirrecion_camino[A]->tam-1, pos_camino[B], pos_camino[A]);
	}
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
	ll N, Q;
	std::cin >> N >> Q;
	for(ll i=0; i < N; i++)
      std::cin >> valor[i];

	ll padre;
	for(ll i=1; i < N; i++){
		std::cin >> padre;
		hijos[padre].push_back(i);
	}

	altura[0] = 0; //Define la altura del primer nodo como 0 pues es el padre
	calcula_pesos(0); //Calcula los pesos desde la raiz hacia abajo

	dirrecion_camino[0] = new camino(-1,0); //Creamos nuestro camino que contiene la raiz, ya que es la raiz diremos que su padre es -1
	pos_camino[0] = 0; //Ya que el primero fue la raiz, sabemos que su posicion es 0 en su respectivo camino
	crea_caminos(0); //Genera el arbol desde la raiz
	ll izq, der, indice, cambio;
  char action;
	for(ll i = 0; i < Q; i++){
    std::cin >> action;//Vemos cual es el rango al que le queremos realizar la accion
		if(action == 'P'){
      std::cin >> izq>> der;
      std::cout << suma(izq, der) << '\n';
		}else{
          std::cin >> indice >> cambio;
		      dirrecion_camino[indice]->updateRange(dirrecion_camino[indice]->tam-1, pos_camino[indice], cambio);
    }
	}
	return 0;
}
