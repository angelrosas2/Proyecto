#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivo.h"
#include "lista.h"

Nodo *lista = NULL;
char bufer[MAX_LINE_LENGTH]; 

Nodo* leerArchivo(const char *nombreArchivo) 
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) 
    {
        perror("No se pudo abrir el archivo");
        return 0;
    }

    while (fgets(bufer, sizeof(bufer), archivo)) 
    {

        bufer[strcspn(bufer, "\n")] = '\0'; /* Remplaza el salto de linea por terminador de cadena*/
        insertarNodo(&lista, bufer); // Solo se usa la producción, no identificadores por ahora
    }

    fclose(archivo);
    return lista;
}
