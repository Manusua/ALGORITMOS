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
  int i, res, minimo, max, ac;
  int **perms;
  clock_t t1,t2;
  perms = genera_permutaciones(n_perms,N);
  if(perms == NULL){return -1;}
    t1 = clock();
    for(i=0;i<n_perms;i++){
      resultado = metodo(perm[i],0,N-1);
      if(res<minimo) minimo = res;
      if(res>max) max = res;
      ac +=res;
  }
  t2 = clock();

  ptiempo->N = N;
  ptiempo->tiempo = (t1+t2)/n_perms;
  ptiempo->min_ob = minimo;
  ptiempo->max_ob = max;
  ptiempo->medio_ob = acum;
  ptiempo->n_elems = n_perms;

  return 0;
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
  /* vuestro codigo */
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  /* vuestro codigo */
}
