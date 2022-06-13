/*
PROBLEMA 2: Denisse Garnica
Solucion:
Crearemos el suffix array del string, pero realmente solo nos importa el primer
elemento de este, pues este sra el inicio de la cadena que estamos buscando, ya
que es el sufijo menor lexicograficamente. Por lo que una vez tengamos este solo
sera necesario agregarle los caracteres que le faltan al final para tener la
respuesta. En clase vimos una construcion del sufix array en O(nlog n), que es
la que usaremos acontinuacion.

*/

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
#define MAX 10000
int frecuencias[MAX];
int suffarray[MAX];
int rankarray[MAX];
int tmprankarray[MAX];
int tmpsuffarray[MAX];
string s;
//Esta funcion aplica el cpunting sort para los sufijos rotados en la posicion >=k
void countingSort(int k) {
    int m=max(100,(int)s.size());
    memset(&frecuencias[0],0,sizeof(frecuencias));
    for (int i=0;i<s.size();i++)
        if (i+k<s.size())
            frecuencias[rankarray[i+k]]++;
        else
            frecuencias[0]++;
    // Acumulado de las frecuencias
    int sfs=0;
    for (int i = 0; i < m; i++) {
        int freq = frecuencias[i];
        frecuencias[i] = sfs;
        sfs += freq;
    }
    //Deduce la posicion de los datos en el arreglo ordenado
    for (int i=0;i<s.size();i++)
        if (suffarray[i]+k<s.size())
            tmpsuffarray[frecuencias[rankarray[suffarray[i]+k]]++] = suffarray[i];
        else
            tmpsuffarray[frecuencias[0]++] = suffarray[i];
    //Copia los datos ordenados
    for (int i=0;i<s.size();i++)
        suffarray[i] = tmpsuffarray[i];
}

void buildSuffArray() {
    for (int i=0;i<s.size();i++)
        rankarray[i] = s[i]-'/';

    // Init the suffix array
    for (int i=0;i<s.size();i++)
        suffarray[i]=i;
    // Does this log n times
    for (int k=1;k<s.size();k<<=1) {
        // Sort according to k+1th element
        countingSort(k);
        // Sort according to first element (this is a stable sort!)
        countingSort(0);
        // Re-generate the ranking based on the sorting
        // The smallest element gets the rank 0
        int r=0;
        tmprankarray[suffarray[0]] = 0;
        for (int i=1;i<s.size();i++)
            if (rankarray[suffarray[i]] != rankarray[suffarray[i-1]] || rankarray[suffarray[i]+k] != rankarray[suffarray[i-1]+k])
                tmprankarray[suffarray[i]] = ++r;
            else
                tmprankarray[suffarray[i]] = r;
        for (int i=0;i<s.size();i++)
            // Update the rank array
            rankarray[i] = tmprankarray[i];
    }
}


int main(){
    cin >> s; //Ingresamos la cadena a procesar
    buildSuffArray(); //Construimos el suffix array
    //recordemos que el suffix array nos devuelve el indice, por lo que solo
    //imprimimos el substring que inicia del indice y despues el substring previo a eso
    cout << s.substr(suffarray[0]) << s.substr(0, suffarray[0]) << endl; //Solo nos interesa el primero y agregar
    return 0;
}
