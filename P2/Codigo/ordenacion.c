#include <stdlib.h>
#include <stdio.h>
#include "ordenacion.h"
int SelectSort(int* tabla, int top, int bottom)
{
  int i,min,j,temp,count=0;
  i = top;
  while(i<bottom){
    min = i;
    for(j=i+1;j<=bottom;j++){
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

int SelectSortInv(int* tabla, int top, int bottom)
{
  int i,max,j,temp,count=0;
  i = top;
  while(i<bottom){
    max = i;
    for(j=i+1;j<=bottom;j++){
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

int combinar(int* tabla, int bottom, int top, int middle){

   int i,jm,kb,contador = 0;
   int* tabla_aux = NULL;
   tabla_aux = (int*)malloc(sizeof(int)*(top-bottom+1));
  printf("hola\n" );
   i=bottom; jm=middle+1; kb=bottom;
   while (kb<=middle && jm<=top) {
     contador++;
     if(tabla[kb] < tabla[jm]){
       tabla_aux[kb] = tabla[i];
       i++;
     }
     else{
       tabla_aux[kb] = tabla[jm];
       jm++;
     }
     kb++;
   }
   if(i>middle){
     while(jm<=top){
       tabla_aux[kb] = tabla[jm];
       jm++;kb++;
     }
   }
   else if(jm>top){
     while(i<= middle){
       tabla_aux[kb] = tabla[i];
       i++;kb++;
     }

   }
   jm=0;
   for(i=bottom;i<=top;i++){
     tabla[i]=tabla_aux[jm];
     jm++;
   }
   free(tabla_aux);
   printf("ADIOS\n" );
   return contador;
}

int MergeSort(int* tabla, int top, int bottom){
  int middle, resultadoc = 0;
  if(tabla == NULL){
    return ERR;
  }
  if(top==bottom) return 0;
  /*Creamos un int para dividir la tabla y volvemos a llamar a la función, esta vez bottom=middle*/
  middle = (top+bottom)/2;
  resultadoc += MergeSort(tabla,bottom,middle);
  if(resultadoc == ERR){
    return ERR;
  }
  /*Trabajamos con la otra mitad de la tabla*/
  resultadoc += MergeSort(tabla,middle+1,top);
  if(resultadoc == ERR){
    return ERR;
  }
  resultadoc += combinar(tabla,bottom, top,middle);
  if(resultadoc == ERR){
    return ERR;
  }
  printf("RESULTADOC: %d\n", resultadoc);
  return resultadoc;

}
