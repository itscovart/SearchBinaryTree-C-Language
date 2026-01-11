#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Diccionario.h"

void read_file(arbolBinario *a, char filename[])
{
  FILE *f = fopen(filename, "r");
  if (!f)
  {
    printf("ERROR: No se pudo abrir el archivo: %s\n", filename);
    return;
  }

  char line[1024];
  while (fgets(line, sizeof(line), f) != NULL)
  {
    size_t n = strlen(line);
    while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r'))
      line[--n] = '\0';

    if (n == 0)
      continue;

    char *sep = strchr(line, ':');
    // if (!sep)
    //   sep = strchr(line, '|');
    // if (!sep)
    //   sep = strchr(line, ';');

    if (!sep)
      continue;

    *sep = '\0';
    char *word = line;
    char *def = sep + 1;

    while (*word == ' ' || *word == '\t')
      word++;
    while (*def == ' ' || *def == '\t')
      def++;

    if (*word == '\0' || *def == '\0')
      continue;

    elemento e;
    memset(&e, 0, sizeof(e));
    strncpy(e.palabra, word, sizeof(e.palabra) - 1);
    strncpy(e.definicion, def, sizeof(e.definicion) - 1);

    add_word(a, e);
  }

  fclose(f);
}

void add_word(arbolBinario *a, elemento e)
{
  if (Vacio(&(*a)))
  {
    *a = (nodo *)malloc(sizeof(nodo));
    if (*a == NULL)
    {
      printf("No se pudo reservar memoria\n");
      exit(1);
    }
    (*a)->hijoIzq = NULL;
    (*a)->hijoDer = NULL;
    (*a)->valor = e;
    return;
  }

  final_node(&(*a), e);
}

void final_node(arbolBinario *a, elemento e)
{
  int cmp = strcmp(e.palabra, (*a)->valor.palabra);

  if (cmp == 0)
  {
    strncpy((*a)->valor.definicion, e.definicion, sizeof((*a)->valor.definicion) - 1);
    (*a)->valor.definicion[sizeof((*a)->valor.definicion) - 1] = '\0';
    return;
  }

  if (cmp < 0)
  {
    if ((*a)->hijoIzq == NULL)
    {
      (*a)->hijoIzq = (nodo *)malloc(sizeof(nodo));
      if ((*a)->hijoIzq == NULL)
      {
        printf("No se pudo reservar memoria\n");
        exit(1);
      }
      (*a)->hijoIzq->hijoIzq = NULL;
      (*a)->hijoIzq->hijoDer = NULL;
      (*a)->hijoIzq->valor = e;
      return;
    }
    final_node(&(*a)->hijoIzq, e);
  }
  else
  {
    if ((*a)->hijoDer == NULL)
    {
      (*a)->hijoDer = (nodo *)malloc(sizeof(nodo));
      if ((*a)->hijoDer == NULL)
      {
        printf("No se pudo reservar memoria\n");
        exit(1);
      }
      (*a)->hijoDer->hijoIzq = NULL;
      (*a)->hijoDer->hijoDer = NULL;
      (*a)->hijoDer->valor = e;
      return;
    }
    final_node(&(*a)->hijoDer, e);
  }
}

elemento elemento_vacio()
{
  elemento e;
  memset(&e, 0, sizeof(e));
  if (sizeof(e.palabra) > 0)
    e.palabra[0] = '\0';
  if (sizeof(e.definicion) > 0)
    e.definicion[0] = '\0';
  return e;
}

elemento search_word(arbolBinario *a, char data[])
{
  if (*a == NULL)
    return elemento_vacio();

  int cmp = strcmp(data, (*a)->valor.palabra);
  if (cmp == 0)
    return (*a)->valor;

  if (cmp < 0)
    return search_word(&(*a)->hijoIzq, data);
  return search_word(&(*a)->hijoDer, data);
}

nodo *find_node(nodo *root, const char *word)
{
  while (root != NULL)
  {
    int cmp = strcmp(word, root->valor.palabra);
    if (cmp == 0)
      return root;
    root = (cmp < 0) ? root->hijoIzq : root->hijoDer;
  }
  return NULL;
}

void modify_word(arbolBinario *a, char word[])
{
  if (*a == NULL)
  {
    printf("Diccionario vacio.\n");
    return;
  }

  nodo *n = find_node(*a, word);
  if (!n)
  {
    printf("La palabra '%s' no existe.\n", word);
    return;
  }

  printf("Definicion actual: %s\n", n->valor.definicion);
  printf("Nueva definicion: ");

  char buf[1024];
  if (!fgets(buf, sizeof(buf), stdin))
    return;

  size_t len = strlen(buf);
  while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r'))
    buf[--len] = '\0';

  if (len == 0)
  {
    printf("No se cambio (definicion vacia).\n");
    return;
  }

  strncpy(n->valor.definicion, buf, sizeof(n->valor.definicion) - 1);
  n->valor.definicion[sizeof(n->valor.definicion) - 1] = '\0';
  printf("Palabra actualizada.\n");
}

nodo *min_node(nodo *root)
{
  while (root && root->hijoIzq)
    root = root->hijoIzq;
  return root;
}

nodo *delete_rec(nodo *root, const char *word, int *deleted)
{
  if (!root)
    return NULL;

  int cmp = strcmp(word, root->valor.palabra);

  if (cmp < 0)
  {
    root->hijoIzq = delete_rec(root->hijoIzq, word, deleted);
    return root;
  }
  if (cmp > 0)
  {
    root->hijoDer = delete_rec(root->hijoDer, word, deleted);
    return root;
  }

  *deleted = 1;

  if (root->hijoIzq == NULL && root->hijoDer == NULL)
  {
    free(root);
    return NULL;
  }

  if (root->hijoIzq == NULL)
  {
    nodo *tmp = root->hijoDer;
    free(root);
    return tmp;
  }
  if (root->hijoDer == NULL)
  {
    nodo *tmp = root->hijoIzq;
    free(root);
    return tmp;
  }

  nodo *succ = min_node(root->hijoDer);
  root->valor = succ->valor;
  root->hijoDer = delete_rec(root->hijoDer, succ->valor.palabra, deleted);
  return root;
}

void delete_word(arbolBinario *a, char word[])
{
  if (*a == NULL)
  {
    printf("Diccionario vacio.\n");
    return;
  }

  int deleted = 0;
  *a = delete_rec(*a, word, &deleted);
  if (deleted)
    printf("Palabra '%s' eliminada.\n", word);
  else
    printf("La palabra '%s' no existe.\n", word);
}

/* Estadísticas */
int count_nodes(nodo *r)
{
  if (!r)
    return 0;
  return 1 + count_nodes(r->hijoIzq) + count_nodes(r->hijoDer);
}

int count_leaves(nodo *r)
{
  if (!r)
    return 0;
  if (!r->hijoIzq && !r->hijoDer)
    return 1;
  return count_leaves(r->hijoIzq) + count_leaves(r->hijoDer);
}

int height(nodo *r)
{
  if (!r)
    return 0;
  int hi = height(r->hijoIzq);
  int hd = height(r->hijoDer);
  return (hi > hd ? hi : hd) + 1;
}

void stats(arbolBinario *a)
{
  if (*a == NULL)
  {
    printf("Diccionario vacio.\n");
    return;
  }

  int n = count_nodes(*a);
  int h = height(*a);
  int leaves = count_leaves(*a);

  printf("\n--- Estadisticas del diccionario ---\n");
  printf("Total de palabras: %d\n", n);
  printf("Altura del arbol:  %d\n", h);
  printf("Hojas:             %d\n", leaves);
  printf("-----------------------------------\n\n");
}
