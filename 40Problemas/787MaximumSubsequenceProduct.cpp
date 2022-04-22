#include<bits/stdc++.h>
#define ll long long

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N;
  while(std::cin>>N){
    std::vector<int> v; //Guarda los valores
    int actual = 0;
    int contador = 0; //Cuenta en cuantas divisiones parte los numeros de ceros
    ll respuesta_f =  -999999;
    ll respuesta_act = 1;
    std::vector<int> n; //Guarda los indices de los negativos
    std::vector<int> zeros; //Guarda los indices de los ceros
    while(N != -999999){
      v.push_back(N);
      if(N == 0){ //Si es 0 hace una nueva division
        zeros.push_back(v.size()-1); //Marcamos donde esta el indice de la division
        contador++; //Aumentamos el num,ero de divisiones
      }
      std::cin >> N;
    }

    zeros.push_back(v.size()); //El ultimo tope es el final del arreglo
    //std::cout << "La cantidad de bloques es "<<  zeros.size() << std::endl;
    for (int i = 0; i < zeros.size(); i++){
      //std::cout << "bloque actual = ["<< actual<< ", " << zeros[i] -1 <<"]" << std::endl;
      std::vector<int> n;
      bool pariedad = 0;
      if(zeros[i] - actual == 1){
        respuesta_act = v[actual];
        if(respuesta_act > respuesta_f)
            respuesta_f = respuesta_act;
        actual = zeros[i] + 1;
        continue;
      }
      //Contamos la pariedad de negativos en el bloque
      for (int j = actual; j < zeros[i]; j++){
          if(v[j] < 0){
              n.push_back(j);
              pariedad = !pariedad; //0 == par, 1 == impar
              //std::cout << "cambio p" << std::endl;
          }
      }
      //std::cout << "La pariedad del bloque es "<<  pariedad << std::endl;

      //Si tenemos un numero par de negativos
      if(pariedad == 0){
          for (int k = actual; k < zeros[i]; k++)
            respuesta_act *= v[k];
      }else{
          ll res_1 = 1;
          ll res_2 = 1;
          //std::cout << "parte 1"<< std::endl;
          for (int k = actual; k < n[n.size()-1]-1; k++){
            //std::cout << "*v[k]" << v[k] << std::endl;
            res_1 *= v[k];
          }
          //std::cout << "parte 2"<< std::endl;
          for (int k = n[0]+1; k < zeros[i]; k++){
            //std::cout << "*v[k]" << v[k] << std::endl;
            res_2 *= v[k];
          }
          respuesta_act = std::max(res_1, res_2);
      }

      if(respuesta_act > respuesta_f)
          respuesta_f = respuesta_act;
      actual = zeros[i] + 1;
    }
    if(respuesta_f < 0 && zeros.size()>1)
      respuesta_f = 0;
    std::cout << respuesta_f << std::endl;
  }
    return 0;
  }
