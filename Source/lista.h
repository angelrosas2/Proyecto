#ifndef LISTA_H
#define LISTA_H

typedef struct Nodo 
{
    char *linea;             
    struct Nodo *liga; 
} Nodo;

Nodo* crearNodo(char *linea);
void insertarNodo(Nodo **cab, char *linea);
void imprimirLista(Nodo *cab);
void liberarLista(Nodo *cab);

#endif
