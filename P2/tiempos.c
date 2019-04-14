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
#include "permutaciones.h"
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/***************************************************/
/* Funcion: tiempo_medio_ordenacion                */
/* Autores: Daniel Gallo y Guillermo García        */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int n,
                              TIEMPO *ptiempo)
{
  int** perms;
  int i;
  int numOB;
  clock_t t1,t2;
  if (metodo == NULL || ptiempo == NULL)
    return ERR;

  printf("Ordenando permutaciones de tamaño %d\n", n);

  perms = genera_permutaciones(n_perms, n);
  if (perms == NULL)
    return ERR;

  ptiempo->N = n;
  ptiempo->n_elems = n_perms;
  t1 = clock();
  for (i = 0; i < n_perms; ++i)
  {
    if(i ==1){
      ptiempo->max_ob = numOB;
      ptiempo->min_ob = numOB;
    }
    numOB = metodo(perms[i], 0, n - 1);
    if (numOB == ERR) {
      /* Limpiamos ptiempo */
      ptiempo->N = 0;
      ptiempo->n_elems = 0;
      ptiempo->tiempo = 0;
      ptiempo->min_ob = 0;
      ptiempo->max_ob = 0;
      ptiempo->medio_ob = 0;
      return ERR;
    }
    if (numOB > ptiempo->max_ob) ptiempo->max_ob = numOB;
    if (numOB < ptiempo->min_ob) ptiempo->min_ob = numOB;
    ptiempo->medio_ob += (double) numOB;
    free(perms[i]);
  }

  t2 = clock();
  ptiempo->medio_ob /= n_perms;
  ptiempo->tiempo = (double)(t2 - t1) / n_perms / CLOCKS_PER_SEC;


  free(perms);
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
  TIEMPO *p_t;
  int i;
  int numP;
  if (metodo == NULL || fichero == NULL)
    return ERR;

  if(incr == 0){
    printf("Error, division entre 0, incremento es igual a 0\n" );
    return ERR;
  }
  numP = (num_max - num_min) / incr + 1;
  if(numP<0){
    printf("Algo ha ido mal\n");
  }
  p_t = malloc(numP * sizeof(TIEMPO));
  if (p_t == NULL)
    return ERR;

  for (i = 0; i < numP; ++i) {
    if (tiempo_medio_ordenacion(metodo, n_perms, num_min + i * incr, &p_t[i]) == ERR)
    {
      free(p_t);
      return ERR;
    }
  }
  if (guarda_tabla_tiempos(fichero, p_t, numP) == ERR)
  {
    free(p_t);
    return ERR;
  }
  else
  {
    free(p_t);
    return OK;
  }
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, TIEMPO *p_t, int n_tiempos)
{
  int i;
  FILE* f;
  if (fichero == NULL || p_t == NULL)
    return ERR;
  f = fopen(fichero, "w");
  if (f == NULL)
    return ERR;
  fprintf(f, "Tamaño\tNúmero de elementos\tTiempo promedio\tMínimo OB\tNúmero promedio OB\tMáximo OB\n");
  for (i = 0; i < n_tiempos; ++i) {
    if (fprintf(f, "%d\t%d\t%f\t%d\t%f\t%d\n", p_t[i].N, p_t[i].n_elems, p_t[i].tiempo, p_t[i].min_ob,
      p_t[i].medio_ob, p_t[i].max_ob) == ERR){
      fclose(f);
      return ERR;
    }
  }
  fclose(f);
  return OK;
}
