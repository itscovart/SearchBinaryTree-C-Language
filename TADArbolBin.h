/*
  Archivo donde se especifican todas las declaraciones de las funciones que se usan para el funcionamiento correcto de una estructura de datos como el arbol binario 
  Autor: Covarrubias Sanchez Arturo
*/

#define TRUE 1
#define FALSE 0
#define word_max 101
#define def_max 251

typedef char boleano;

typedef struct elemento{
  char palabra[word_max];
  char definicion[def_max];
} elemento;

typedef struct nodo{
  elemento valor;
  struct nodo* hijoIzq;
  struct nodo* hijoDer;
} nodo;

typedef nodo* arbolBinario;
typedef nodo* posicion;

void Inicializar(arbolBinario *a);
void Destruir(arbolBinario *a);

posicion Raiz(arbolBinario *a);
posicion Padre(arbolBinario *a,posicion p);
posicion HijoDerecho(arbolBinario *a,posicion p); 
posicion HijoIzquierdo(arbolBinario *a,posicion p);
posicion Buscar(arbolBinario *a,elemento e);

boleano Vacio(arbolBinario *a);
boleano NodoNulo(arbolBinario *a,posicion p);//

elemento LeerNodo(arbolBinario *a,posicion p);

void NuevoHijoDerecho(arbolBinario *a,posicion p,elemento e); 
void NuevoHijoIzquierdo(arbolBinario *a,posicion p,elemento e); 
void BorrarHijoDerecho(arbolBinario *a,posicion p); 
void BorrarHijoIzquierdo(arbolBinario *a,posicion p); 
void BorrarNodo(arbolBinario *a,posicion p); 
void ReemplazarNodo(arbolBinario *a,posicion p,elemento e);

void ImprimirElemento(elemento e);
void PreOrden(arbolBinario *a, posicion p);
void InOrden(arbolBinario *a, posicion p);
void PostOrden(arbolBinario *a, posicion p);