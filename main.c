#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Diccionario.h"

void trim_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[--n] = '\0';
    }
}

void read_line(const char *prompt, char *buf, size_t cap) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (!fgets(buf, (int)cap, stdin)) {
        buf[0] = '\0';
        return;
    }
    trim_newline(buf);
}

int read_int(const char *prompt) {
    char buf[64];
    read_line(prompt, buf, sizeof(buf));
    return atoi(buf);
}

void print_menu(void) {
    printf("\n================ DICCIONARIO (ABB) ================\n");
    printf("1) Cargar un archivo de definiciones\n");
    printf("2) Agregar una palabra y su definicion\n");
    printf("3) Buscar una palabra\n");
    printf("4) Modificar una definicion\n");
    printf("5) Eliminar una palabra\n");
    printf("6) Recorrido PreOrden\n");
    printf("7) Recorrido InOrden\n");
    printf("8) Recorrido PostOrden\n");
    printf("9) Estadisticas del ABB\n");
    printf("0) Salir\n");
    printf("==================================================\n");
}

int main(void) {
    arbolBinario diccionario;
    Inicializar(&diccionario);

    for (;;) {
        print_menu();
        int op = read_int("Selecciona una opcion: ");
        system("clear");

        if (op == 0) {
            printf("Saliendo...\n");
            break;
        }

        if (op == 1) {
            char filename[256];
            read_line("Nombre del archivo (ej. diccionario.txt): ", filename, sizeof(filename));
            if (filename[0] == '\0') {
                printf("Nombre de archivo vacio.\n");
                continue;
            }
            read_file(&diccionario, filename);
            printf("Archivo cargado (si existia).\n");
        }
        else if (op == 2) {
            elemento e;
            memset(&e, 0, sizeof(e));

            read_line("Palabra: ", e.palabra, sizeof(e.palabra));
            if (e.palabra[0] == '\0') {
                printf("Palabra vacia.\n");
                continue;
            }
            read_line("Definicion: ", e.definicion, sizeof(e.definicion));
            if (e.definicion[0] == '\0') {
                printf("Definicion vacia.\n");
                continue;
            }

            add_word(&diccionario, e);
            printf("Palabra agregada/actualizada.\n");
        }
        else if (op == 3) {
            char word[256];
            read_line("Palabra a buscar: ", word, sizeof(word));
            if (word[0] == '\0') {
                printf("Palabra vacia.\n");
                continue;
            }

            elemento r = search_word(&diccionario, word);
            if (r.palabra[0] != '\0') {
                printf("\nENCONTRADA\n");
                printf("%s: %s\n", r.palabra, r.definicion);
            } else {
                printf("La palabra '%s' no existe.\n", word);
            }
        }
        else if (op == 4) {
            char word[256];
            read_line("Palabra a modificar: ", word, sizeof(word));
            if (word[0] == '\0') {
                printf("Palabra vacia.\n");
                continue;
            }

            modify_word(&diccionario, word);
        }
        else if (op == 5) {
            char word[256];
            read_line("Palabra a eliminar: ", word, sizeof(word));
            if (word[0] == '\0') {
                printf("Palabra vacia.\n");
                continue;
            }

            delete_word(&diccionario, word);
        }
        else if (op == 6) {
            printf("\n--- PREORDEN ---\n");
            PreOrden(&diccionario, Raiz(&diccionario));
        }
        else if (op == 7) {
            printf("\n--- INORDEN (ORDENADO) ---\n");
            InOrden(&diccionario, Raiz(&diccionario));
        }
        else if (op == 8) {
            printf("\n--- POSTORDEN ---\n");
            PostOrden(&diccionario, Raiz(&diccionario));
        }
        else if (op == 9) {
            stats(&diccionario);
        }
        else {
            printf("Opcion invalida.\n");
        }
    }

    Destruir(&diccionario);
    return 0;
}
