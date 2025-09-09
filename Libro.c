# include <stdio.h>
# include <stdlib.h>
# include "Libro.h"


// Lee la cadena caracter por caracter para determinar su espacio de memoria
char* espacioDeMemoria() {
    
    char* cadena = NULL;
    int caracteres = 0;
    int c;

    while (( c = getchar()) != '\n' && c != EOF) { //Fuente: https://rabbit.eng.miami.edu/class/een218/getchar.html
        char* capacidad = realloc(cadena,( caracteres+2) * sizeof(char));//Se suma 2 para que quepa el caracter y '/0'
        if (capacidad == NULL) {
            printf("Error en la asignacion de memoria\n");
            free(capacidad);
            exit(1);
        }
        cadena = capacidad;
        cadena[caracteres] = (char)c;//'\0'
        caracteres+=1;
    }
   
    if (cadena != NULL) {
        cadena[caracteres] = '\0';
    }
    //capacidad[caracteres] = '\0';

    //return capacidad;
    return cadena;
}

Libro CrearLibro() {
    Libro lib;
    lib.nombreLibro = NULL;
    lib.precioLibro = (float*)malloc(sizeof(float));
    lib.cantidad = (int*)malloc(sizeof(int));
    lib.codigoLibro = 0;
    return lib;
}

int obtenerSiguienteCodigo() {
    FILE *archi = fopen(ARCHIVO_LIBROS, "r");
    if (!archi) {
        return 1; // Si no existe el archivo, empezamos en LIB1
    }

    int codigo = 0;
    while (fscanf(archi, "Codigo: LIB%d\n", &codigo) == 1) {
        // Guarda el último código leído
    }

    fclose(archi);
    return codigo + 1;
}

void registrarLibro(Libro *lib) {
    printf("Nombre del libro: ");
    lib->nombreLibro = espacioDeMemoria();

    printf("Precio del libro: ");
    scanf("%f", lib->precioLibro);

    printf("Cantidad: ");
    scanf("%d", lib->cantidad);

    lib->codigoLibro = obtenerSiguienteCodigo();

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // limpiar buffer
}

void guardarLibroEnTXT(Libro *lib) {
    FILE *archi = fopen(ARCHIVO_LIBROS, "a");
    if (!archi) {
        perror("No se pudo abrir el archivo");
        return;
    }

    fprintf(archi, "Codigo: LIB%d\n", lib->codigoLibro);
    fprintf(archi, "Nombre: %s\n", lib->nombreLibro ? lib->nombreLibro : "(sin nombre)");
    fprintf(archi, "Precio: %.2f\n", lib->precioLibro ? *lib->precioLibro : 0.0f);
    fprintf(archi, "Cantidad: %d\n", lib->cantidad ? *lib->cantidad : 0);
    fprintf(archi, ";\n");

    fclose(archi);

    printf("\nLibro LIB%d registrado exitosamente\n\n", lib->codigoLibro);
    system("pause");
    printf("\n");
    
}

void LiberarMemoriaLibro(Libro *lib) {
    free(lib->nombreLibro);
    free(lib->precioLibro);
    free(lib->cantidad);
    lib->nombreLibro = NULL;
    lib->precioLibro = NULL;
    lib->cantidad = NULL;
}

int iniciarPrograma() {
    int opcion;

    while (1) {
        printf("-------------------INVENTARIO DE LIBRERIA-------------------\n");
        printf("-----------------------MENU PRINCIPAL-----------------------\n\n");
        printf("Ingresa el NUMERO de alguna de las opciones:\n\n");
        printf("1. Registrar libro\n");
        printf("2. Inventario (no implementado)\n");
        printf("3. Registrar cliente (no implementado)\n");
        printf("4. Crear pedido (no implementado)\n");
        printf("5. Estadistica (no implementado)\n");
        printf("6. Salir\n");

        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1: {
                Libro lib = CrearLibro();
                registrarLibro(&lib);
                guardarLibroEnTXT(&lib);
                LiberarMemoriaLibro(&lib);
                break;
            }
            case 6:
                return 0;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    }
}


