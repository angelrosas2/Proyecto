#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivo.h"
#include "lista.h"

Nodo* leerArchivo(const char *nombreArchivo) 
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) 
    {
        perror("No se pudo abrir el archivo");
        return 0;
    }

    Nodo *lista = NULL;
    char bufer[256]; 

    while (fgets(bufer, sizeof(bufer), archivo)) 
    {

        bufer[strcspn(bufer, "\n")] = '\0'; /*La función retorna el número de caracteres leídos de
                                            la subcadena hasta que halla alguno de los caracteres de "\n". El carácter nulo no se cuenta.*/

        insertarNodo(&lista, bufer);
    }

    fclose(archivo);
    return lista;
}
