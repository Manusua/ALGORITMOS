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


#include "ordenacion.h"

/***************************************************/
/* Funcion: InsertSort    Fecha:                   */
/* Vuestro comentario                              */
/***************************************************/
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
  /* vuestro codigo */
}
