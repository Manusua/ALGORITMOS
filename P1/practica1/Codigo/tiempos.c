/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include "tiempos.h"
#include "ordenacion.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int N,
                              PTIEMPO ptiempo)
{
  int i, res, minimo, max, ac = 0;
  int **perms;
  clock_t t1,t2;
  perms = genera_permutaciones(n_perms,N);
  if(perms == NULL){return ERR;}
    t1 = clock();
    for(i=0;i<n_perms;i++){
      res = metodo(perms[i],0,N-1);
      if(res<minimo || i == 0) minimo = res;
      if(res>max || i == 0) max = res;
      ac +=res;
  }
  t2 = clock();

  ptiempo->N = n_perms;
  ptiempo->tiempo = (t2-t1)/n_perms;
  ptiempo->min_ob = minimo;
  ptiempo->max_ob = max;
  ptiempo->medio_ob = ac/n_perms;
  ptiempo->n_elems = N;

/*TODO: comprobacion de errores*/

  return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha:       */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
  int i, cont = 0;
  PTIEMPO tiempo;
  tiempo = malloc(sizeof(PTIEMPO)*((num_max-num_min)/(incr)));
  if(!tiempo){
    return ERR;
  }
  for (i = num_min; i<=num_max; i+=incr){
    tiempo_medio_ordenacion(metodo,n_perms,i,&tiempo[cont]);
    cont++;
  }
  guarda_tabla_tiempos(fichero, tiempo,(num_max-num_min)/(incr));
return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  int i;
  FILE *fp;
      printf("LLEGO AQI\n" );
  fp = fopen(fichero, "a");

  for(i=0;i<n_tiempos;i++){
    fprintf(fp, "%d %f %d %f %d \n", tiempo[i].n_elems, tiempo[i].tiempo, tiempo[i].min_ob, tiempo[i].medio_ob, tiempo[i].max_ob);
  }
 fclose(fp);
 return OK;
}
