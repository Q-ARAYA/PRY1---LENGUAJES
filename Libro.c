# include <stdio.h>
# include <stdlib.h>
# include "buffer.h"

typedef struct {
    char* nombreLibro;
    //char* caracteres;
    float* precioLibro;
    int codigoLibro;
    int* cantidad;
} Libro;

Libro CrearLibro() {

    Libro lib;
    //lib.caracteres = (char *)malloc(100 * sizeof(char));
    lib.nombreLibro = NULL;
    lib.precioLibro = (float*)malloc(sizeof(float));
    lib.cantidad = (int*)malloc(sizeof(int));
    lib.codigoLibro = 0;
    return lib;
}

void registrarLibro(Libro *lib) { //struct Libro* libro

    printf("Nombre del libro:");
    
    //scanf("%s", lib->nombreLibro);
    lib->nombreLibro = espacioDeMemoria();

    printf("Precio del libro: ");
    scanf("%f", lib->precioLibro);

    printf("Cantidad: ");
    scanf("%d", lib->cantidad);

    lib->codigoLibro += 1;
    int c = getchar(); //Fuente: https://rabbit.eng.miami.edu/class/een218/getchar.html
    while (c != '\n' && c != EOF) {
       
    }
}

void guardarLibroEnTXT(Libro *lib){
    FILE *archi = fopen("Libros.txt", "a"); // append para no sobrescribir
    if (!archi) {
        perror("No se pudo abrir Libros.txt");
        return;
    }

    fprintf(archi, "Nombre: %s\n", lib->nombreLibro ? lib->nombreLibro : "(sin nombre)");
    fprintf(archi, "Precio: %.2f\n", lib->precioLibro ? *lib->precioLibro : 0.0f);
    fprintf(archi, "Codigo: %d\n", lib->codigoLibro);
    fprintf(archi, "Cantidad: %d\n", lib->cantidad ? *lib->cantidad : 0);
    fprintf(archi, ";\n");
    fclose(archi);

    printf("\nLibro registrado exitosamente \n\n");
    system("pause");
}

//void eliminarLibro(Libro *lib {
    
    
//}

void LiberarMemoriaLibro(Libro *lib) {
    free(lib->nombreLibro);
    free(lib->precioLibro);
    //free(lib->caracteres);
    //free(lib->codigoLibro);
    free(lib->cantidad);
    lib->nombreLibro = NULL;
    lib->precioLibro = NULL;
    //lib->caracteres = NULL;
    lib->cantidad = NULL;
}

int main() {
    int opcion;

    while (1){
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
            // Crear libro vacío
            Libro lib = CrearLibro();
            registrarLibro(&lib);
            guardarLibroEnTXT(&lib);
            LiberarMemoriaLibro(&lib);
            break;

        case 6:
            return 0;
        
        default:
            break;
        }
    }

}

