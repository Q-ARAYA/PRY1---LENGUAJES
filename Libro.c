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
    printf("Libro registrado exitosamente\nEl codigo del libro es el siguiente: %d\n", lib->codigoLibro);

    int c = getchar(); //Fuente: https://rabbit.eng.miami.edu/class/een218/getchar.html
    while (c != '\n' && c != EOF) {
       
    }
}

void guardarInformacion(Libro *lib){
    FILE *archi;
    char p1 = (lib->nombreLibro);
    float *p2 = (lib->precioLibro);
    int p3 = (lib->codigoLibro);
    int p4 = (lib->cantidad);

    archi = fopen("c:\\TEC CODIGO\\Lenguajes\\Proyectos\\P1\\Libros.txt","w");
    fprintf(archi, "______________________\n");
    fprintf(archi, "Nombre: %c\n", p1);
    //fprintf(archi,"\n");
    fprintf(archi, "Precio: %f\n", p2);
    fprintf(archi, "Codigo: %d\n", p3);
    fprintf(archi, "Cantidad: %d\n", p4);
    fprintf(archi, "______________________\n");
    fclose(archi);
}

//void eliminarLibro(Libro *lib {
    
    
//})

void LiberarMemoria(Libro *lib) {
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
    
    Libro lib = CrearLibro();
    registrarLibro(&lib);
    //guardarInformacion(&lib);
    LiberarMemoria(&lib);
    
    return 0;
}

