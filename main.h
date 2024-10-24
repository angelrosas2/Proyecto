#include <stdio.h>
#include <strlib.h>
#include <string.h>

#define LARGO_MAX_LINEA 100

//Estructura del nodo para la lista
typedef struct Nodo
{
    char *idenficador;
    char *produccion;
    struct Nodo *sig;
}NODO;

Node* crearNodo (const char *Identificador, cost char *produccion)