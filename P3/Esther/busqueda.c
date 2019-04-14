/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}


PDICC ini_diccionario (int tamanio, char orden)
{
	PDICC pdicc;
  pdicc = malloc(sizeof(DICC));
  if ( pdicc == NULL)
    return NULL;
  pdicc->tabla = malloc(sizeof(int)*tamanio);
  if(pdicc->tabla == NULL){
    free(pdicc);
    return NULL;
  }
  pdicc->tamanio = tamanio;
  pdicc->orden = orden;
  pdicc->n_datos = 0;
  return pdicc;
}

void libera_diccionario(PDICC pdicc)
{
	if(pdicc == NULL)
    return;
  if(pdicc->tabla != NULL)
    free(pdicc->tabla);
  free(pdicc);
}

int inserta_diccionario(PDICC pdicc, int clave)
{
  int i;

	if( pdicc == NULL)
    return ERR;
  if(pdicc->n_datos == pdicc->tamanio)
    return ERR;

  pdicc->tabla[pdicc->n_datos]=clave;

  if(pdicc->orden == ORDENADO){
     /*insertamos al final y luego bamos bajando el elemento*/

    for (i = pdicc->n_datos -1; i >= 0 && pdicc->tabla[i] > clave; i--)
      pdicc->tabla[i+1] = pdicc->tabla[i];

    pdicc->tabla[i+1] = clave;

  }

  pdicc->n_datos++;

  return OK;
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
	int j,ret = OK;

  if( claves == NULL )
    return ERR;

  for( j = 0; j< n_claves; j++){
    ret = inserta_diccionario(pdicc, claves[j]);
    if(ret == ERR)
      break;
  }

  return ret;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	if(ppos == NULL)
    return ERR;
  return metodo(pdicc->tabla, 0, pdicc->n_datos, clave, ppos);
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla,int P,int U,int clave,int *ppos)
{
	int m,u=U-1,obs = 0;

  while(P <= u){
    m = (P+u)/2;
    obs++;
    if(tabla[m] == clave){
      *ppos=m;
      return obs;
    }
    else if(tabla[m] > clave)
      u=m-1;
    else
      P=m+1;
  }
  *ppos = NO_ENCONTRADO;
  return obs;
}

int blin(int *tabla,int P,int U,int clave,int *ppos)
{
  int i, obs = 0;

  for(i = 0; i < U; i++){
    obs++;
    if(tabla[i] == clave){
      *ppos=i;
      return obs;
    }
  }
  *ppos = NO_ENCONTRADO;
  return obs;

}
