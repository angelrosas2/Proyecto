#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funcion para crear un nodo

NODO* creaNodo(const char *regla, const char *prod)
{
    NODO *nuevoN = (NODO *)malloc(sizeof(NODO));
    nuevoN->regla = strdup(regla);
    nuevoN->prod = strdup(prod);
    nuevoN->sig = NULL;
    nuevoN->ant = NULL;

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

// Función para agregar producción
void agregProduc(NODO *nod, const char *prod) 
{
    // Verifica si la producción ya está en nod->prod para evitar duplicados
    if (!strstr(nod->prod, prod)) {
        size_t nuevoTam = strlen(nod->prod) + strlen(prod) + 4;
        nod->prod = (char *)realloc(nod->prod, nuevoTam);

        // Solo agrega " | " si nod->prod no está vacío
        if (strlen(nod->prod) > 0) {
            strcat(nod->prod, " | ");
        }
        strcat(nod->prod, prod);
    }
}


//Función para agregar un nuevo nodo o actualizar uno existente

void agregActNodo(NODO **cab, const char *regla, const char *prod) {
    NODO *exisNodo = encontrarNodo(*cab, regla);
    if (exisNodo) {
        agregProduc(exisNodo, prod); // Si lo encontró, agrega la producción
    } else {
        NODO *nuevoN = creaNodo(regla, prod);
        if (!*cab) {
            *cab = nuevoN;
        } else {
            NODO *aux = *cab;
            while (aux->sig) {
                aux = aux->sig;
            }
            aux->sig = nuevoN;
            nuevoN->ant = aux;
        }
    }
}

//Funcion para librerar un lista enlazada

void liberarListaEnlazada(NODO *cab)
{
    NODO *actual= cab;
    NODO *sigNodo;

    while (actual != NULL)
    {
        sigNodo = actual->sig;
        free(actual->regla);
        free(actual->prod);
        free(actual);
        actual = sigNodo;
    }
}

// Función para dividir una línea en identificador de regla y producción
void dividirLinea(const char *linea, char *regla, char *prod) 
{
    // Encontrar la posición de "->" en la línea
    const char *delimitador = strstr(linea, "->");
    if (delimitador != NULL) {
        // Copiar la parte antes de "->" en la regla
        strncpy(regla, linea, delimitador - linea);
        regla[delimitador - linea] = '\0';  // Colocar el terminador nulo al final de "regla"

        // Copiar la parte después de "->" en la producción
        strcpy(prod, delimitador + 2);  // Se salta el "->"
    }
}

// Función para crear una lista doblemente enlazada a partir de un archivo
NODO* crearLinkedLista(FILE *archivo) {
    NODO *cab = NULL;
    char linea[256];
    char regla[256];
    char prod[256];
    while (fgets(linea, sizeof(linea), archivo)) 
    {
        linea[strcspn(linea, "\n")] = '\0';
        dividirLinea(linea, regla, prod);
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

//PASO 2 Hacia abajo
void primeraSustitucion(NODO *cab) 
{
    NODO *actual = cab;
    while (actual) 
    {
        // Buscar patrones de la forma A -> aA
        char *prod = actual->prod;
        char *token = strtok(strdup(prod), " | ");
        char nuevaProd[1024] = "";
        int primero = 1;
        
        while (token) 
        {
            if (strlen(token) >= 2 && token[strlen(token)-1] == actual->regla[0]) 
            {
                // Es de la forma aA
                if (!primero) strcat(nuevaProd, " | ");
                char temp[256];
                snprintf(temp, sizeof(temp), "{%c}", token[0]);
                strcat(nuevaProd, temp);
                if (strlen(token) > 2) 
                {
                    // Si hay más caracteres entre 'a' y 'A'
                    strcat(nuevaProd, "(");
                    strncat(nuevaProd, token + 1, strlen(token) - 2);
                    strcat(nuevaProd, ")");
                }
            } else {
                if (!primero) strcat(nuevaProd, " | ");
                strcat(nuevaProd, token);
            }
            primero = 0;
            token = strtok(NULL, " | ");
        }
        
        // Actualizar la producción
        free(actual->prod);
        actual->prod = strdup(nuevaProd);
        
        // Realizar sustitución descendente
        NODO *siguiente = actual->sig;
        while (siguiente) 
        {
            char *pos = strstr(siguiente->prod, actual->regla);
            if (pos) 
            {
                char nuevaProd[1024] = "";
                size_t preLen = pos - siguiente->prod;
                strncpy(nuevaProd, siguiente->prod, preLen);
                strcat(nuevaProd, actual->prod);
                strcat(nuevaProd, pos + strlen(actual->regla));
                
                free(siguiente->prod);
                siguiente->prod = strdup(nuevaProd);
            }
            siguiente = siguiente->sig;
        }
        
        actual = actual->sig;
    }
}


//PASO 3 hacia arriba
void segundaSustitucion(NODO *cab) 
{
    // Ir al último nodo
    NODO *actual = cab;
    while (actual->sig) 
        actual = actual->sig;
    
    while (actual) 
    {
        // Buscar patrones de la forma A -> aA
        char *prod = actual->prod;
        char *token = strtok(strdup(prod), " | ");
        char nuevaProd[1024] = "";
        int primero = 1;
        
        while (token) 
        {
            if (strlen(token) >= 2 && token[strlen(token)-1] == actual->regla[0]) 
            {
                // Es de la forma aA
                if (!primero) strcat(nuevaProd, " | ");
                char temp[256];
                snprintf(temp, sizeof(temp), "{%c}", token[0]);
                strcat(nuevaProd, temp);
                if (strlen(token) > 2) 
                {
                    strcat(nuevaProd, "(");
                    strncat(nuevaProd, token + 1, strlen(token) - 2);
                    strcat(nuevaProd, ")");
                }
            } else {
                if (!primero) strcat(nuevaProd, " | ");
                strcat(nuevaProd, token);
            }
            primero = 0;
            token = strtok(NULL, " | ");
        }
        
        // Actualizar la producción
        free(actual->prod);
        actual->prod = strdup(nuevaProd);
        
        // Realizar sustitución ascendente
        NODO *anterior = actual->ant;
        while (anterior) 
        {
            char *pos = strstr(anterior->prod, actual->regla);
            if (pos) 
            {
                char nuevaProd[1024] = "";
                size_t preLen = pos - anterior->prod;
                strncpy(nuevaProd, anterior->prod, preLen);
                strcat(nuevaProd, actual->prod);
                strcat(nuevaProd, pos + strlen(actual->regla));
                
                free(anterior->prod);
                anterior->prod = strdup(nuevaProd);
            }
            anterior = anterior->ant;
        }
        
        actual = actual->ant;
    }
}



// Reemplazo de "{x}" por "x*"
void reemplazarLlavesPorAsterisco(NODO *cab) 
{
    NODO *actual = cab;
    while (actual) 
    {
        char *prod = actual->prod;
        char nuevaProd[1024] = "";
        char *pos = prod;
        
        while (*pos) 
        {
            if (*pos == '{') 
            {
                char *cierre = strchr(pos, '}');
                if (cierre && (cierre - pos) == 2) 
                {
                    // Encontramos un patrón {x}
                    strncat(nuevaProd, pos + 1, 1);  // Añadir x
                    strcat(nuevaProd, "*");          // Añadir *
                    pos = cierre + 1;
                } else 
                {
                    strncat(nuevaProd, pos, 1);
                    pos++;
                }
            } 
            else 
            {
                strncat(nuevaProd, pos, 1);
                pos++;
            }
        }
        
        free(actual->prod);
        actual->prod = strdup(nuevaProd);
        actual = actual->sig;
    }
}

void ImpExpRegRes(NODO *cab) 
{
    if (cab == NULL) 
        return NULL;
    printf("La Expresion resultante es: %s\n", cab->prod);
}


int main()
{

// PASO 1 AGRUPAR REGLAS

    FILE *archivo = fopen("Resources/gramatica2.txt","r");
    if(archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    //ListaDoblementeEnlazada
    NODO *cab = crearLinkedLista(archivo);
    fclose(archivo);
        
    //Imprimir reglas agrupadas
    printf("Paso no. 1: \nLas Expresiones agrupadas son: \n");
    imprimirLista(cab); 

//PASO 2 SUSTITUCION DESCENDENTE
    primeraSustitucion(cab);
    printf("\nPaso no. 2:\n1era Sustitucion: \n");
    imprimirLista(cab); 

//PASO 3 SUSTITUCION ASCENDENTE
    segundaSustitucion(cab);
    printf("\nPaso no. 3:\n2nda Sustitucion: \n");
    imprimirLista(cab); 

//Remplazo de coincidencias con el patrón "{a}" por "a*":
    reemplazarLlavesPorAsterisco(cab);
    printf("\n Asteriscos Cambiados \n");
    imprimirLista(cab); 

    //imprimirLista(cab);

//IMPRIMIR EXPRESION REGULAR RESULTANTE 
    ImpExpRegRes(cab); 

    //Liberar la lista
    liberarListaEnlazada(cab);

    return 0;
}



