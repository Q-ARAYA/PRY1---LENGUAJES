#include <stdio.h>
#include <stdlib.h>
#ifndef BUFFER_H
#define BUFFER_H

// Lee la cadena caracter por caracter para determinar su espacio de memoria
char* espacioDeMemoria() {
    
    char* cadena = NULL;
    int caracteres = 0;
    int c;
    
    char* capacidad = (char*)malloc((caracteres+1) * sizeof(char));
    c = getchar();

    while (( c = getchar()) != '\n' && c != EOF) { //Fuente: https://rabbit.eng.miami.edu/class/een218/getchar.html
        capacidad = realloc(cadena,( caracteres+2) * sizeof(char));//Se suma 2 para que quepa el caracter y '/0'
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

#endif