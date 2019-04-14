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
#include <stdio.h>
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
  if(claves == NULL || n_claves <= 0 || max <= 0){
    return;
  }
  if(LOG) printf("Generando claves...\n");
  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);
  return;
}


PDICC ini_diccionario (int tamanio, char orden)
{
  PDICC pdicc;

  if(LOG) printf("Iniciando diccionario...\n");

  if(tamanio <= 0) return NULL;
  if(orden != ORDENADO && orden != NO_ORDENADO) return NULL;

  pdicc = (PDICC) malloc(sizeof(DICC));
  if(pdicc == NULL) return NULL;

  pdicc->tamanio = tamanio;
  /*En n_datos tenemos el numero del indice (o sea, es el numero de datos -1)*/
  pdicc->n_datos = 0;
  pdicc->orden = orden;
  pdicc->tabla = (int*)malloc(tamanio*sizeof(int));
  if(pdicc->tabla == NULL){
    free(pdicc);
    return NULL;
  }
  if(LOG) printf("Diccionario Iniciado correctamente...\n");
  return pdicc;
}

void libera_diccionario(PDICC pdicc)
{
  if(LOG) printf("Liberando Diccionario\n");
	if(pdicc == NULL || pdicc->tabla == NULL) return;

  free(pdicc->tabla);
  free(pdicc);
  if(LOG) printf("Diccionario liberado correctamente\n");
  return;
}

int inserta_diccionario(PDICC pdicc, int clave)
{
  int j, A;
  if(pdicc == NULL || pdicc->tamanio <= pdicc->n_datos) return ERR;
  if(pdicc->n_datos > pdicc->tamanio){
    printf("Error tamanio maximo superado\n");
    return ERR;
  }

  if(pdicc->n_datos == pdicc->tamanio){
    pdicc->tabla = realloc(pdicc->tabla, pdicc->tamanio*2*sizeof(int));
    if (pdicc->tabla == NULL){ /*comprueo si falla el realloc*/
      libera_diccionario(pdicc);
      return ERR;
    }
    pdicc->tamanio = pdicc->tamanio*2;
  }

  pdicc->tabla[pdicc->n_datos] = clave;
  if(pdicc->orden == NO_ORDENADO){
    pdicc->n_datos++;
    return OK;
  }
  else if(pdicc->orden == ORDENADO){

    /*ordenar*/
    j = pdicc->n_datos;
    A = pdicc->tabla[j];

    while(j > 0 && pdicc->tabla[j-1] > A){

      pdicc->tabla[j] = pdicc->tabla[j-1];
      pdicc->tabla[j-1] = A;
      j--;
    }

    pdicc->n_datos++;
    return OK;
  }
  return ERR;
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
	int i;
  if(n_claves < 1 || claves == NULL) return ERR;
  if(LOG) printf("Comienzo de insercion masiva\n");
  for(i = 0; i<n_claves; i++){
    if(inserta_diccionario(pdicc, claves[i]) == ERR) return ERR;
  }
  if(LOG) printf("Fin de insercion masiva\n");
  return OK;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
  if(LOG) printf("Inicio de busqueda en diccionario...\n");

  if(pdicc == NULL) return ERR;
  if(ppos == NULL) return ERR;

  if(LOG) printf("Fin de busqueda en diccionario\n");
	return metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos);
}

/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla,int P,int U,int clave,int *ppos)
{
  int OBS = 0, medio;
  if(tabla == NULL || P < 0 || P > U || ppos == NULL) return ERR;
  /*Si la tabla solo tiene 1 elemento hay que comprobar si es la clave*/
  if(P == U){
    if(tabla[U] == clave){
      *ppos = U;
    }else{
      *ppos = NO_ENCONTRADO;
    }
    /*devolvemos 1 ya que hace 1 CDC*/
    return 1;
  }

  while(P <= U){
    medio = (P+U)/2;
    /*si el medio es clave --> OB++*/
    OBS++;
    if(tabla[medio] == clave){
        *ppos = medio;
        return OBS;
    }else if(tabla[medio] > clave){
        U = medio-1;
    }else{
      P = medio + 1;
    }
  }
  return OBS;
}

int blin(int *tabla,int P,int U,int clave,int *ppos)
{
  int i, OBS = 0;

  if(tabla== NULL || P > U || P < 0) return ERR;
  if (P == U){
    if(tabla[P] == clave){
      *ppos = P;
    }else{
      *ppos = NO_ENCONTRADO;
    }
    return 1;
  }

  for(i=P;i<=U;i++){
    OBS++;
    if(tabla[i] == clave){
      (*ppos) = i;
      return OBS;
    }
  }
  *ppos = NO_ENCONTRADO;
  return OBS;
}
