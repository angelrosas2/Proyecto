#ifndef LISTA_H
#define LISTA_H

#define MAX_LINE_LENGTH 100

// Estructura del nodo
typedef struct Nodo 
{
    char *ruleIdentifier;    // Identificador de regla
    char *production;        // Producción
    struct Nodo *liga;       // Liga al siguiente nodo
} Nodo;

Nodo* crearNodo(const char *ruleIdentifier, const char *production);
void insertarNodo(Nodo **cab, const char *ruleIdentifier, const char *production);
void imprimirLista(Nodo *cab);
void liberarLista(Nodo *cab);

#endif
