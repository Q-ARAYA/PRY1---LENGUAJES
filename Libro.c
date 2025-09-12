#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Libro.h"
#include "Cliente.h"

// -------------------------------------Guardar LIBRO------------------------------------------------------------------------------------

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


}

void LiberarMemoriaLibro(Libro *lib) {
    free(lib->nombreLibro);
    free(lib->precioLibro);
    free(lib->cantidad);
    lib->nombreLibro = NULL;
    lib->precioLibro = NULL;
    lib->cantidad = NULL;
}

// --------------------------------------------------Eliminar LIBRO----------------------------------------------------------------------

void eliminarLibro(const char* codigoBuscado){
    FILE *original = fopen("Libros.txt", "r");
    if (!original) {
        printf("No se pudo abrir Libros.txt\n");
        return;
    }

    FILE *temp = fopen("Temp.txt", "w"); // archivo temporal para almacenar los libros que no se van a borrar
    if (!temp) {
        printf("No se pudo crear archivo temporal\n");
        fclose(original);
        return;
    }

    char linea[256];
    bool encontrado = false;
    bool copiar = true;

    while (fgets(linea, sizeof(linea), original)) {
        if (strncmp(linea, "Codigo:", 7) == 0) {
            if (strstr(linea, codigoBuscado)) {
                encontrado = true;
                copiar = false;
            } else {
                copiar = true;
            }
        }

        if (copiar) {
            fputs(linea, temp);
        }

        if (linea[0] == ';') {
            copiar = true;
        }
    }

    fclose(original);
    fclose(temp);

    if (remove("Libros.txt") != 0 || rename("Temp.txt", "Libros.txt") != 0) {
        perror("Error al actualizar archivo");
        return;
    }

    if (encontrado) {
        printf("\nLibro %s eliminado correctamente.\n\n", codigoBuscado);
    } else {
        printf("\nNo se encontró el libro con código %s.\n\n", codigoBuscado);
    }
}


// --------------------------------------------------Funcs Auxliares----------------------------------------------------------------------

char* solicitarCodigo(){
    char* codigo = malloc(20 * sizeof(char));;
    printf("Ingrese el codigo del libro EJEMPLO (LIB4)");
    scanf("%19s", codigo);
    return codigo;
}

// --------------------------------------------------MENU PRINCIPAL---------------------------------------------------------------------

void inventarioDePrograma() {
    int opcion;

    // while para que el programa no termine si no se selecciona salir
    while (1) {
        printf("-------------------INVENTARIO DE LIBRERIA-------------------\n");
        printf("Ingresa el NUMERO de alguna de las opciones:\n\n");
        printf("1. Eliminar libro\n");
        printf("2. Modificar Inventario (no implementado)\n");
        printf("3. Eliminar cliente\n");
        printf("6. Volver\n");

        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1: {
                
                char* codigo = solicitarCodigo();
                eliminarLibro(codigo);
                free(codigo);
                system("pause");
                printf("\n");
                break;
            }

            case 2: {

            }

            case 3: {
                char* cedula = solicitarCedula();
                eliminarCliente(cedula);
                free(cedula);
                system("pause");
                printf("\n");
                break;
            }
            case 6:
                return;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    }
}

int iniciarPrograma() {
    int opcion;

    // while para que el programa no termine si no se selecciona salir
    while (1) {
        printf("-------------------INVENTARIO DE LIBRERIA-------------------\n");
        printf("-----------------------MENU PRINCIPAL-----------------------\n\n");
        printf("Ingresa el NUMERO de alguna de las opciones:\n\n");
        printf("1. Registrar libro\n");
        printf("2. Inventario\n");
        printf("3. Registrar cliente\n");
        printf("4. Crear pedido (no implementado)\n");
        printf("5. Estadistica (no implementado)\n");
        printf("6. Salir\n");

        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1: {
                // Funciones para generar el libro y guardar en el .txt automaticamente
                Libro lib = CrearLibro();
                registrarLibro(&lib);
                guardarLibroEnTXT(&lib);
                LiberarMemoriaLibro(&lib);
                system("pause");
                printf("\n");
                break;
            }

            case 2: {
                inventarioDePrograma();
                break;
            }

            case 3: {
                registrarCliente();
                system("pause");
                printf("\n");
                break;
            }
            case 6:
                return;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    }
}


