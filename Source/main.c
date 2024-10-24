#include <stdio.h>
#include "lista.h"
#include "archivo.h"

int main() 
{
    printf("Inicialización\n");

    const char *nombreArchivo = "gramatica7.txt"; // gramática (1,2,7 etc)...
    Nodo *lista = leerArchivo(nombreArchivo);

    // Verificación de lista
    if (lista == NULL) 
    {
        printf("No se pudo leer el archivo o está vacío.\n");
        return 1;  
    }

    printf("Contenido del archivo:\n");
    imprimirLista(lista);
    liberarLista(lista);

    printf("Finalización\n");

    return 0;
}
