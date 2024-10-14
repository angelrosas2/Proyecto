#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Nodo* crearNodo(char *linea) 
{
    Nodo *nvo = (Nodo*)malloc(sizeof(Nodo));
    if (!nvo) 
    {
        printf("Operación fallida");
        return 0;
    }
    nvo->linea = strdup(linea); 
    nvo->liga = NULL;
    return nvo;
}

void insertarNodo(Nodo **cab, char *linea) 
{
    Nodo *nvo = crearNodo(linea);
    if (!*cab) 
        *cab = nvo; 
    else
    {
        Nodo *aux = *cab;
        while (aux->liga != NULL) 
            aux = aux->liga;
        aux->liga = nvo;
    }
}

void imprimirLista(Nodo *cab)
{
    Nodo *aux = cab;
    while (aux != NULL) 
    {
        printf("%s\n", aux->linea);
        aux = aux->liga;
    }
}

void liberarLista(Nodo *cab) 
{
    Nodo *aux;
    while (cab) 
    {
        aux = cab;
        cab = cab->liga;
        free(aux->linea);  
        free(aux);        
    }
}
