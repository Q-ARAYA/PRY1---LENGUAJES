#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

typedef struct {
    char* nombreLibro;
    char* caracteres;
    float* precioLibro;
    int codigoLibro;
    int* anioPublicacion;
} Libro;

Libro CrearLibro() {

    Libro lib;
    lib.caracteres = (char *)malloc(100 * sizeof(char));
    lib.nombreLibro = NULL;
    lib.precioLibro = (float*)malloc(sizeof(float));
    lib.anioPublicacion  = (int*)malloc(sizeof(int));
    lib.codigoLibro = 0;
    return lib;
}

void registrarLibro(Libro *lib) { //struct Libro* libro

    printf("Nombre del libro:");
    
    scanf("%s", lib->caracteres);
    lib->nombreLibro = espacioDeMemoria(lib->caracteres);

    printf("Precio del libro: ");
    scanf("%f", lib->precioLibro);

    printf("Anio de publicacion: ");
    scanf("%d", lib->anioPublicacion);

    lib->codigoLibro += 1;
    printf("Libro registrado exitosamente, el codigo del libro es el siguiente: %d\n", lib->codigoLibro);
}

void LiberarMemoria(Libro *lib) {
    free(lib->nombreLibro);
    free(lib->precioLibro);
    free(lib->caracteres);
    //free(lib->codigoLibro);
    free(lib->anioPublicacion);
}

int main() {
    // Crear libro vacío
    Libro lib = CrearLibro();
    int opcion;
    //Aqui se va a codificar el menu principal
    printf ("----INVENTARIO DE LIBRERIA----\n");
    printf ("--------MENU PRINCIPAL--------\n\n");
    printf ("Ingresa el NUMERO de alguna de la opciones:\n\n");
    printf ("1. Registrar libro\n");
    printf ("2. Inventario\n");
    printf ("3. Registrar cliente\n");
    printf ("4. Crear pedido\n");
    printf ("5. Estadistica\n");
    printf ("6. Salir\n");

    scanf ("%d", &opcion);
    getchar();

    switch (opcion) {
    case 1:
        registrarLibro(&lib);
        break;
    
    case 6:
        return 0;
    
    default:
        break;
    }

    // Registrar datos desde el usuario
    registrarLibro(&lib);

    // Liberar memoria
    LiberarMemoria(&lib);

    return 0;
}
