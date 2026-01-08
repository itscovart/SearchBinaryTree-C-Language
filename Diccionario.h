#include "TADArbolBin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(arbolBinario *a, char filename[]);
void add_word(arbolBinario *a, elemento e);

void final_node(arbolBinario *a, elemento e);
elemento elemento_vacio();
elemento search_word(arbolBinario *a, char data[]);
nodo *find_node(nodo *root, const char *word);
void modify_word(arbolBinario *a, char word[]);
nodo *min_node(nodo *root);
nodo *delete_rec(nodo *root, const char *word, int *deleted);
void delete_word(arbolBinario *a, char word[]);

int count_nodes(nodo *r);
int count_leaves(nodo *r);
int height(nodo *r);
void stats(arbolBinario *a);