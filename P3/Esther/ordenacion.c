/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "ordenacion.h"

/***************************************************/
/* Funcion: InsertSort    Fecha:                   */
/* Vuestro comentario                              */
/***************************************************/
int SelectSort(int* tabla, int ip, int iu)
{
  /* vuestro codigo */
  int i,j,m,dum, op=0;
  if (tabla == NULL)
    return ERR;
  i = ip;
  while(i < iu){
    m = i;
    for(j = i+1;j <= iu;j++){
      op++;
      if(tabla[j] < tabla[m]){
        m = j;
      }
    }
    dum = tabla[m];
  	tabla[m] = tabla[i];
  	tabla[i] = dum;
    i++;
  }
  return op;
}

int SelectSortInv(int* tabla, int ip, int iu)
{
  int i,j,m,dum, op=0;
  if(tabla == NULL)
    return ERR;
  i = ip;
  while(i < iu){
    m = i;
    for(j = i+1;j <= iu;j++){
      op++;
      if(tabla[j] > tabla[m]){
        m = j;
      }
    }
    dum = tabla[m];
    tabla[m] = tabla[i];
    tabla[i] = dum;
    i++;
  }
  return op;
}

int Merge(int *tabla, int P, int U, int M){

  int *aux;
  int i,j,k, cont=0;
  if (tabla == NULL)
    return ERR;
    /*No comprobamos si P>U o P==U ya que se comprueba siempre en la función MergeSort antes de llamar a esta*/
  aux = malloc((U-P+1)*sizeof(int));/*Tamaño que va a tener la tabla*/
  if(aux == NULL)
    return ERR;

  i = P;
  j = M+1;
  k = 0; /*Porque la tabla auxiliar empieza en 0*/
  while(i <= M && j <= U){
    cont++;
    if(tabla[i] < tabla[j]){
      aux[k] = tabla[i];
      i++;
    }
    else{
      aux[k] = tabla[j];
      j++;}
    k++;
    }

  if(i > M){
    while(j <= U){
      aux[k] = tabla[j];
      j++;
      k++;
    }
  }
  else if (j > U){
    while(i <= M){
      aux[k] = tabla[i];
      i++;
      k++;
     }
   }
    for(i = 0;i < (U-P+1);i++){
      tabla[i+P] = aux[i];
    }
    free(aux);
    return cont;
  }

int MergeSort(int *tabla, int P, int U){
  int M;
  int ret1,ret2,ret;
  if (tabla == NULL)
    return ERR;
  if(P > U)
    return ERR;

  if (P == U)
    return 0;

  M = (P+U)/2;
  ret1 = MergeSort(tabla,P,M);
  if (ret1 == ERR)
    return ERR;
  ret2 = MergeSort(tabla, M+1,U);
  if (ret2 == ERR)
    return ERR;
  ret = Merge(tabla,P,U,M);
   if (ret == ERR)
    return ERR;
  return ret1+ret2+ret;
  }


  int medio(int *tabla, int ip, int iu,int *pos){
      if(tabla == NULL || pos == NULL)
        return ERR;
      *pos = ip;
      return 0;
  }

  int partir(int* tabla, int ip, int iu,int *pos){
    int ret,k,i,aux;
    int ob=0;

    if (tabla == NULL || pos == NULL)
      return ERR;
    ret = medio(tabla,ip,iu,pos);
    if (ret == ERR)
      return ERR;
    k = tabla[*pos]; /*Pasos que en nuestro caso no causan ningún efecto, ya que para nosotros *pos = ip, pero lo dejamos para futuras implementaciones
                      con el punto medio diferente*/
    tabla[*pos] = tabla[ip];
    tabla[ip] = k;
    *pos = ip;
    ob++;
    for (i = ip+1;i <= iu;i++){
      if (tabla[i] < k){
        (*pos)++;
        aux = tabla[i];
        tabla[i] = tabla[*pos];
        tabla[*pos] = aux;
        ob++;
      }
    }
    aux = tabla[ip];
    tabla[ip] = tabla[*pos];
    tabla[*pos] = aux;
    ob++;
    return ob;

  }

  int QuickSort(int* tabla, int ip, int iu){
    int ret1=0, ret2=0, ret3=0;
    int pos;
    if (tabla == NULL)
      return ERR;
    if (ip > iu)
      return ERR;
    if (ip == iu)
      return 0;
    else
      ret1 = partir(tabla, ip, iu, &pos);
    if (ret1 == ERR)
      return ERR;
    if (ip < pos-1){
      ret2 = QuickSort(tabla, ip, pos-1);
      if (ret2 == ERR)
        return ERR;
      }
    if (pos+1 < iu){
      ret3 = QuickSort(tabla,pos+1,iu);
      if (ret3 == ERR)
        return ERR;
      }

    return ret1+ret2+ret3;
  }

  int QuickSort_sr (int* tabla, int ip, int iu) {
    int pos,ret;
    int OBs = 0;
    if(tabla == NULL)
      return ERR;
    if (ip == iu)
      return 0;
    if (ip > iu)
      return ERR;


    while (ip < iu) {
      ret = partir(tabla, ip, iu, &pos);
      if(ret == ERR)
        return ERR;

      OBs += ret;

      if ((pos - ip) < (iu - pos)) {
        if(ip < pos - 1){
          ret = QuickSort_sr(tabla, ip, pos - 1);
          if(ret == ERR)
            return ERR;
          OBs += ret;
        }
        ip = pos + 1;

      } else {
        if(iu > (pos + 1)){
          ret = QuickSort_sr(tabla, pos + 1, iu);
          if(ret == ERR)
            return ERR;
          OBs += ret;
        }
        iu = pos - 1;

      }
    }
    return OBs;
  }
