#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Estructura de Nodo

typedef struct NODO {
char *regla;
char *prod;
struct NODO *sig;
} NODO;

//Funciones 
NODO* crearNodo(const char *regla, const char *prod);
void agregNodo(NODO **cab, const char *regla, const char *prod);
void liberarListaEnlazada(NODO *cab);
NODO* crearLinkedLista(FILE *file);
void imprimirLista(NODO *cab);

void dividirLinea(const char *linea, char *regla, char *prod);
NODO* encontrarNodo(NODO *cab, const char *regla);
void agregProduc(NODO *nod, const char *prod);
void agregActNodo(NODO **cab, const char *regla);