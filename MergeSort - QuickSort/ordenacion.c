

#include <stdlib.h>
#include <stdio.h>
#include "ordenacion.h"

int SelectSort(int* tabla, int ip, int iu)
{
  int i,min,j,temp,count=0;
  i = ip;
  while(i<iu){
    min = i;
    for(j=i+1;j<=iu;j++){
      if(tabla[j]<tabla[min]){
        min = j;
      }
      count++;
    }
    temp = tabla[i];
    tabla[i] = tabla[min];
    tabla[min] = temp;
    i++;
  }
  return count;
}

int SelectSortInv(int* tabla, int ip, int iu)
{
  int i,max,j,temp,count=0;
  i = ip;
  while(i<iu){
    max = i;
    for(j=i+1;j<=iu;j++){
      if(tabla[j]>tabla[max]){
        max = j;
      }
      count++;
    }
    temp = tabla[i];
    tabla[i] = tabla[max];
    tabla[max] = temp;
    i++;
  }
  return count;
}


int merge(int *tabla, int ip, int iu, int imedio){
  /*COMPROBAR ARG*/
  int *tabla_aux;
  int i=0,j=0,k=0;
  int contador=0;

  tabla_aux = malloc((iu-ip+1)*sizeof(int));/*Tamaño q va a tener la tabla*/
  if(tabla_aux==NULL) return ERR;

  i=ip;
  j=imedio+1;
  k=0; /*Porque la tabla auxiliar empieza en 0*/
  while(i<=imedio && j<=iu){
    contador++;
    if(tabla[i]<tabla[j]){
      tabla_aux[k]=tabla[i];
      i++;
    }
    else{
      tabla_aux[k]=tabla[j];
      j++;
    }
      k++;
    }

  if(i>imedio){
    while(j<=iu){
      tabla_aux[k]=tabla[j];
      j++;
      k++;
    }
  }
  else if (j>iu){
    while(i<=imedio){
      tabla_aux[k]=tabla[i];
      i++;
      k++;
     }
   }

    for(i=0;i<(iu-ip+1);i++){
      tabla[ip+i]=tabla_aux[i];
    }
    free(tabla_aux);
    return contador;
  }

int MergeSort(int *tabla, int ip, int iu){
  int medio;
  int obs1,obs2,obsC;
  if(ip>iu) return ERR;
  if(ip==iu) return 0;

  medio=(ip+iu)/2;
  obs1=MergeSort(tabla,ip,medio);
  if(obs1==ERR)
    return ERR;
  obs2=MergeSort(tabla, medio+1,iu);
  if(obs2==ERR)
    return ERR;
  obsC=merge(tabla, ip, iu, medio);
   if(obsC==ERR)
    return ERR;
  return (obs1+obs2+obsC);
}


int medio(int *tabla, int ip, int iu,int *pos){
  if(ip > iu)
    return ERR;
  if(ip == iu)
    return ip;
  (*pos) = iu-ip/2 + 1;
  return 0;
}

int partir(int* tabla, int ip, int iu, int * pi){
  int i, pivote, k, aux, aux2;
  aux2 = 0;
  if(tabla == NULL)
    return ERR;
  if(medio(tabla, ip, iu, &pivote) == ERR)
    return ERR;
  k = tabla[pivote];
  aux = tabla[ip];
  tabla[ip] = tabla[pivote];
  tabla[pivote] = aux;

  pivote = ip;
  /*TODO OJO AL iu QUE ES =>*/
  for(i = ip + 1;i <= iu; i++){
    aux2++;
    if(tabla[i]<k){
      pivote++;
      aux = tabla[pivote];
      tabla[pivote] = tabla[i];
      tabla[i] = aux;
    }
  }
  aux = tabla[pivote];
  tabla[pivote] = tabla[ip];
  tabla[ip] = aux;
  (*pi) = pivote;
  return aux2;
}


int quicksort_src(int* tabla, int ip, int iu){
  int pi, aux;
  if(ip >= iu)
    return ERR;
  while (ip < iu){
      aux = partir(tabla, ip, iu, &pi);
      if (ip < pi - 1){
          aux += quicksort_src(tabla, ip, pi - 1);
      }
      ip = pi + 1;
    }
    return aux;
}

int quicksort(int* tabla, int ip, int iu){
  int ret, aux;
  aux = 0;
  if(ip >= iu)
    return ERR;
  if(ip < iu){
  ret = partir(tabla, ip, iu, &aux);
  if(ip < ret -1)
    aux += quicksort(tabla, ip, ret -1);
  if(ret + 1)
    aux += quicksort(tabla, ret + 1, iu);
  }
  return aux;
}
