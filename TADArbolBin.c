/*
  Archivo donde se especifica toda la logica que llevan las funciones declaradas en el archivo con extension .h
  Autor: Covarrubias Sanchez Arturo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADArbolBin.h"

void Inicializar(arbolBinario *a)
{
  *a = NULL;
}

void Destruir(arbolBinario *a)
{
  if (*a != NULL)
  {
    if ((*a)->hijoIzq != NULL)
    {
      Destruir(&(*a)->hijoIzq);
    }
    else if ((*a)->hijoDer != NULL)
    {
      Destruir(&(*a)->hijoDer);
    }
    free(*a);
    *a = NULL;
  }
}

posicion Raiz(arbolBinario *a)
{
  return *a;
}

posicion Padre(arbolBinario *a, posicion p)
{
  posicion padre = NULL;
  if (*a != NULL)
  {
    if ((*a)->hijoIzq == p || (*a)->hijoDer == p)
    {
      padre = *a;
    }

    if ((*a)->hijoIzq != NULL)
      padre = Padre(&((*a)->hijoIzq), p);

    if ((*a)->hijoDer != NULL)
      padre = Padre(&((*a)->hijoDer), p);
  }
  else
  {
    printf("ERROR: la posicion dada no es valida (Padre)");
    exit(1);
  }
  return padre;
}

posicion HijoDerecho(arbolBinario *a, posicion p)
{
  posicion regreso = NULL;
  if (!NodoNulo(&(*a), p))
  {
    regreso = p->hijoDer;
  }
  else
  {
    printf("ERROR: La posicion dada no es valida (Hijo Derecho)");
  }
  return regreso;
}

posicion HijoIzquierdo(arbolBinario *a, posicion p)
{
  posicion regreso = NULL;
  if (!NodoNulo(&(*a), p))
  {
    regreso = p->hijoIzq;
  }
  else
  {
    printf("ERROR: La posicion dad no es valida (Hijo Izquierdo)");
  }
  return regreso;
}

posicion Buscar(arbolBinario *a, elemento e)
{
  posicion p = NULL;
  if (!Vacio(&(*a)))
  {
    if (memcmp(&((*a)->valor), &e, sizeof(elemento)) == 0)
    {
      p = *a;
    }

    if ((*a)->hijoIzq != NULL)
      p = Buscar(&(*a)->hijoIzq, e);

    if ((*a)->hijoDer != NULL && p == NULL)
      p = Buscar(&(*a)->hijoDer, e);
  }
  return p;
}

boleano Vacio(arbolBinario *a)
{
  return ((*a) == NULL);
}

boleano NodoNulo(arbolBinario *a, posicion p)
{
  boleano respuesta = TRUE;
  if (!(*a == NULL || p == NULL))
  {
    if (!(*a == p))
    {
      if ((*a)->hijoIzq != NULL)
        respuesta = NodoNulo(&((*a)->hijoIzq), p);
      if ((*a)->hijoDer != NULL && respuesta == TRUE)
        respuesta = NodoNulo(&((*a)->hijoDer), p);
    }
    else
    {
      respuesta = FALSE;
    }
  }
  return respuesta;
}

elemento LeerNodo(arbolBinario *a, posicion p)
{
  if (!NodoNulo(&(*a), p))
  {
    return p->valor;
  }
  else
  {
    printf("ERROR: la posicion no es valida (Leer Nodo)");
    exit(1);
  }
}

void NuevoHijoDerecho(arbolBinario *a, posicion p, elemento e)
{
  if (Vacio(&(*a)))
  {
    *a = malloc(sizeof(nodo));
    if (*a == NULL)
    {
      printf("No se pudo reservar memoria");
      exit(1);
    }
    (*a)->hijoIzq = NULL;
    (*a)->hijoDer = NULL;
    (*a)->valor = e;
  }
  else if (!NodoNulo(&(*a), p))
  {
    if (p->hijoDer != NULL)
    {
      printf("ERROR: La posicion p ya tiene un hijo derecho (Nuevo Hijo Derecho)");
      exit(1);
    }
    p->hijoDer = malloc(sizeof(nodo));
    p->hijoDer->hijoIzq = NULL;
    p->hijoDer->hijoDer = NULL;
    p->hijoDer->valor = e;
  }
  else
  {
    printf("ERROR: La posicion dada no es valida (Nuevo Hijo Derecho)");
    exit(1);
  }
}

void NuevoHijoIzquierdo(arbolBinario *a, posicion p, elemento e)
{
  if (Vacio(&(*a)))
  {
    *a = malloc(sizeof(nodo));
    if (*a == NULL)
    {
      printf("No se pudo reservar memoria");
      exit(1);
    }
    (*a)->hijoIzq = NULL;
    (*a)->hijoDer = NULL;
    (*a)->valor = e;
  }
  else
  {
    if (!NodoNulo(&(*a), p))
    {
      if (p->hijoIzq != NULL)
      {
        printf("ERROR: La posicion p ya tiene un hijo izquierdo (Nuevo Hijo Izquierdo)");
        exit(1);
      }
      p->hijoIzq = malloc(sizeof(nodo));
      p->hijoIzq->hijoIzq = NULL;
      p->hijoIzq->hijoDer = NULL;
      p->hijoIzq->valor = e;
    }
    else
    {
      printf("ERROR: La posicion dada no es valida (Nuevo Hijo Izquierdo)");
      exit(1);
    }
  }
}

void BorrarHijoDerecho(arbolBinario *a, posicion p)
{
  if (!NodoNulo(&(*a), p))
  {
    Destruir(&p->hijoDer);
    p->hijoDer = NULL;
  }
  else
  {
    printf("ERROR: La posicion dada no es valida (Destruir hijo derecho)");
    exit(1);
  }
}

void BorrarHijoIzquierdo(arbolBinario *a, posicion p)
{
  if (!NodoNulo(&(*a), p))
  {
    Destruir(&p->hijoIzq);
    p->hijoIzq = NULL;
  }
  else
  {
    printf("ERROR: La posicion dada no es valida (Destruir hijo derecho)");
    exit(1);
  }
}

void BorrarNodo(arbolBinario *a, posicion p)
{
  if (!NodoNulo(&(*a), p))
  {
    posicion padre = Padre(a, p);
    if (padre->hijoDer == p)
    {
      padre->hijoDer = NULL;
    }
    else if (padre->hijoIzq == p)
    {
      padre->hijoIzq = NULL;
    }
    Destruir(&p);
  }
  else
  {
    printf("ERROR: La posicion no es valida (Borrar Nodo)");
    exit(1);
  }
}

void ReemplazarNodo(arbolBinario *a, posicion p, elemento e)
{
  if (!NodoNulo(&(*a), p))
  {
    p->valor = e;
  }
  else
  {
    printf("ERROR: La posicion dada no es valida (Reemplazar Nodo)");
    exit(1);
  }
}

void ImprimirElemento(elemento e)
{
  printf("%s: %s\n", e.palabra, e.definicion);
}

void PreOrden(arbolBinario *a, posicion p)
{
  if (p == NULL)
    return;

  ImprimirElemento(LeerNodo(a, p));
  PreOrden(a, HijoIzquierdo(a, p));
  PreOrden(a, HijoDerecho(a, p));
}

void InOrden(arbolBinario *a, posicion p)
{
  if (p == NULL)
    return;

  InOrden(a, HijoIzquierdo(a, p));
  ImprimirElemento(LeerNodo(a, p));
  InOrden(a, HijoDerecho(a, p));
}

void PostOrden(arbolBinario *a, posicion p)
{
  if (p == NULL)
    return;

  PostOrden(a, HijoIzquierdo(a, p));
  PostOrden(a, HijoDerecho(a, p));
  ImprimirElemento(LeerNodo(a, p));
}