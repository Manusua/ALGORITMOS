#include <stdio.h>
#include <stdlib.h>
#include "ordenacion.h"


int main(){
  int* tabla;
  int aaa;
  tabla = (int*)malloc(sizeof(int)*6);
  tabla[0] = 3;
  tabla[1] = 1;
  tabla[2] = 5;
  tabla[3] = 4;
  tabla[4] = 2;
  tabla[5] = 6;
  aaa = MergeSort(tabla, 0, 5);
  printf("Operacoinkjdsgfuyyreio: %d\n", aaa);





  return 0;
}
