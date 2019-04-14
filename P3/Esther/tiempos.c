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
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiempos.h"
#include "permutaciones.h"

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                                int orden, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_veces)
{

    int i, size, cont=0, ST=OK;
    PTIEMPO ptiempo;

    if(fichero==NULL)
      return ERR;
    size=(num_max-num_min)/incr + 1;
    ptiempo=(PTIEMPO)malloc(size*sizeof(TIEMPO));
    if(ptiempo==NULL)
      return ERR;


    for(i=num_min;i<=num_max;i+=incr){
      ST=tiempo_medio_busqueda(metodo, generador, orden, i, n_veces, &ptiempo[cont]);
      if(ST == ERR)
        break;
      cont++;
    }
    if(ST==ERR){
      free(ptiempo);
      return ERR;
    }

    ST=guarda_tabla_tiempos(fichero, ptiempo, size);

    free(ptiempo);

    return ST;
}

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int N,
                              int n_veces,
                              PTIEMPO ptiempo)
{
  PDICC pdicc;
  int *perm;
  int ret, j, FLAG = OK;
  double acum = 0;
  int *tabla;
  int pos;
  clock_t t1,t2;

  if(N <= 0 || n_veces <= 0 || ptiempo == NULL || metodo == NULL || generador == NULL){
      printf("Error con argumentos en funcion tiempo_medio_busqueda\n");
      return ERR;
  }

  pdicc = ini_diccionario(N,orden);
  if(pdicc == NULL){
    printf("No se pudo crear el diccionario\n");
    return ERR;
  }

  perm = genera_perm(N);
  if(perm == NULL){
    printf("No se pudo crear la permutacion\n");
    libera_diccionario(pdicc);
    return ERR;
  }

  ret = insercion_masiva_diccionario(pdicc, perm, N);
  if(ret == ERR){
    printf("No se pudo insertar en el diccionario\n");
    FLAG = ERR;
    goto liberar;
  }

  tabla = (int*)malloc(sizeof(int)*n_veces*N);
  if(tabla == NULL){
    printf("Error al crear la tabla que contiene las claves\n");
    FLAG = ERR;
    goto liberar;
  }

  generador(tabla,n_veces*N,N);

  t1=clock();
  if(t1 == ERR){
    FLAG = ERR;
    goto liberar1;
  }
  ptiempo->max_ob = 0;
  ptiempo->min_ob = 0;

  for(j=0;j<N*n_veces;j++){
    ret = busca_diccionario(pdicc,tabla[j],&pos,metodo);

    if(ret == ERR){
      FLAG = ERR;
      break;
    }
    if(ret>ptiempo->max_ob)
      ptiempo->max_ob = ret;
    if(ret < ptiempo->min_ob || ptiempo->min_ob==0)
      ptiempo->min_ob = ret;

    acum+=((double)ret)/(N*n_veces); /*Ya hemos comprobado al inicio que N+n_veces no da cero*/
  }
  if(FLAG == ERR)
    goto liberar1;

  t2 = clock();
  if(t2 == ERR){
    FLAG = ERR;
    goto liberar1;
  }
  ptiempo->medio_ob=acum;
  ptiempo->N = N;
  ptiempo->n_elems = N*n_veces;
  ptiempo->tiempo = ((double)(t2-t1)/(N*n_veces))/CLOCKS_PER_SEC;

  liberar1:
  free(tabla);
  liberar:
  free(perm);
  libera_diccionario(pdicc);

  return FLAG;

}


/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  FILE *fp;
  int i;

  if(fichero==NULL)
    return ERR;


  fp=fopen(fichero, "w");
  if(fp==NULL)
    return ERR;
  for(i=0;i<n_tiempos;i++){
    if(fprintf(fp,"%d %.10f %d %f %d\n", tiempo[i].N, tiempo[i].tiempo, tiempo[i].min_ob, tiempo[i].medio_ob, tiempo[i].max_ob)<0)
      break;
  }
  if(fclose(fp)==ERR)
    return ERR;
  if(i<n_tiempos)
    return ERR;
  return OK;
}
