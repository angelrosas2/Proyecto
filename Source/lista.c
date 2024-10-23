#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Función para crear un nodo nuevo
Nodo* crearNodo(const char *ruleIdentifier, const char *production) 
{
    Nodo *nvo = (Nodo *)malloc(sizeof(Nodo));
    if (!nvo) 
    {
        printf("Operación fallida al asignar memoria\n");
        return NULL;
    }

    nvo->ruleIdentifier = strdup(ruleIdentifier);  // Duplicar el identificador
    nvo->production = strdup(production);          // Duplicar la producción
    if (!nvo->ruleIdentifier || !nvo->production) 
    {
        free(nvo->ruleIdentifier);
        free(nvo->production);
        free(nvo);
        return NULL;
    }

    nvo->liga = NULL;
    return nvo;
}

// Función para insertar un nodo en la lista
void insertarNodo(Nodo **cab, const char *ruleIdentifier, const char *production) 
{
    Nodo *nvo = crearNodo(ruleIdentifier, production);
    if (!nvo) return;  // Manejo de error si la creación del nodo falla

    if (!*cab) 
    {
        *cab = nvo;
    }
    else 
    {
        Nodo *aux = *cab;
        while (aux->liga != NULL) 
            aux = aux->liga;
        aux->liga = nvo;
    }
}

// Función para imprimir la lista
void imprimirLista(Nodo *cab)
{
    Nodo *aux = cab;
    while (aux) 
    {
        printf("Identificador: %s, Producción: %s\n", aux->ruleIdentifier[0] ? aux->ruleIdentifier : "(Sin identificador)", aux->production);
        aux = aux->liga;
    }
}

// Función para liberar la memoria de la lista
void liberarLista(Nodo *cab) 
{
    Nodo *aux;
    while (cab) 
    {
        aux = cab;
        cab = cab->liga;
        free(aux->ruleIdentifier);  
        free(aux->production);      
        free(aux);                  
    }
}
