#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funcion para crear un nodo

NODO* creaNodo(const char *regla, const char *prod)
{
    NODO *nuevoN = (NODO *)malloc(sizeof(NODO));
    nuevoN->regla= strdup(regla);
    nuevoN->prod= strdup(prod);
    nuevoN->sig= NULL;

    return(nuevoN);
}

//Función para encontar un nodo por regla identidad

NODO* encontrarNodo(NODO *cab, const char *regla)
{
    NODO *actual=cab;

    while(actual)
    {
        if(strcmp(actual->regla, regla)==0)
            return(actual);
        
        actual= actual->sig;
    }
    return(NULL); //se retorna NULL si no lo encontró

}

//Funcion para agregar producción 

void agregProduc(NODO *nod, const char *prod)
{
    size_t nuevoTam= strlen(nod->prod) + strlen(prod) + 4;
    nod->prod= (char *)realloc(nod->prod, nuevoTam);

    strcat(nod->prod, " | ");
    strcat(nod->prod, prod);

}

//Función para agregar un nuevo nodo o actualizar uno existente

void agregActNodo(NODO **cab, const char *regla, const char *prod)
{
    NODO *exisNodo= encontrarNodo(*cab, regla);

    if(exisNodo)
    {
        agregProduc(exisNodo, prod); //Si lo encontró, agrega la producción
    }
    else{
        NOO *nuevoN= creaNodo(regla, prod);

        if(!*cab)
            *cab= nuevoN;
        else{
            NODO *aux=*cab;

            while (aux->sig)
            {
                aux=aux->sig;
            }

            aux->sig= nuevoN;
            
        }
    }
}

//Funcion para librerar un lista enlazada

void liberarListaEnlazada(NODO *cab)
{
    NODO *actual= cab;
    NODO *sigNodo;

    while (actual)
    {
        sigNodo= actual->sig;
        free(actual->regla);
        free(actual->prod);
        free(actual);
        actual = actual->sig;
    }
}

//Funcion para divir una linea en identificador de regla y produccion

void dividirLinea(const char *linea, char *regla, char *prod)
{
    //Encontrar la posicion de "->" en la linea
    const char *delimitador = strstr(linea, "->");
    if(delimitador != NULL)
    {
        //copiar la parte antes de "->" en la regla
        strncpy(regla, linea, delimitador - linea);
        regla[delimitador - linea] = '\n';

        //copiar la parte despues de "->" en a produccion
        strcpy(prod, delimitador + 2); //se salta el "->"
    }

}

//Funcion una lista enlazada a partir de un archivo
NODO* crearLinkedLista(FILE *archivo)
{
    NODO *cab = NULL;
    char linea[MAX_LINE_LENGTH];
    char regla[MAX_LINE_LENGTH];
    char prod[MAX_LINE_LENGTH];

    //Leer el archivo linea por linea y almacenar cada linea en un nuevo nodo o actualizarlo
    while (fget(linea, sizeof(linea), archivo))
    {

        //eliminar el carácter de nueva línea si está presente
        linea[strcspn(linea, "\n")] = '\0';

        //dividir la linea en la regla y la produccion
        dividirLinea(linea, regla, produccion);

        //agregar o actualizar el nodo en la lista enlazada
        agregActNodo(&cab, regla, prod);
    }

return cab;
}

//Funcion para imprimir la lista enlazada
void imprimirLista(NODO* cab)
{
    NODO *actual = cab;
    while(actual != NULL)
    {
        printf("%s -> %s\n", actual->regla, actual -> prod);
        actual = actual->sig;
    }
}

int main()
{
    FILE *archivo = fopen("gramatica1.txt","r");
    if(archivo == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    NODO *cab = crearLinkedLista(archivo);

    fclose(archivo);

    //imprimir la lista Enlazada
    imprimirLista(cab);

    //Liberar la lista
    liberarListaEnlazada(cab);

    return 0;
}