#include "../headers/Admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern char* espacioDeMemoria();

bool verificarCredenciales() {
    FILE *archi = fopen(ARCHIVO_CREDENCIALES, "r");
    if (!archi) {
        printf("Error: No se pudo abrir el archivo de credenciales.\n");
        return false;
    }

    char *usuarioArchivo = malloc(50 * sizeof(char));
    char *contraArchivo = malloc(50 * sizeof(char));
    
    // Leer usuario y contraseña del archivo
    fscanf(archi, "%49s", usuarioArchivo);
    fscanf(archi, "%49s", contraArchivo);
    fclose(archi);

    // Solicitar credenciales al usuario
    printf("\n=== AUTENTICACION ADMINISTRATIVA ===\n");
    printf("Usuario: ");
    char* usuario = espacioDeMemoria();
    
    printf("Contrasenia: ");
    char* password = espacioDeMemoria();

    // Verificar credenciales
    bool autenticado = (strcmp(usuario, usuarioArchivo) == 0 && 
                       strcmp(password, contraArchivo) == 0);

    // Liberar memoria
    free(usuario);
    free(password);
    free(usuarioArchivo);
    free(contraArchivo);

    return autenticado;
}

bool autenticarAdministrativo() {
    while (true) {
        if (verificarCredenciales()) {
            printf("\nAutenticacion exitosa: Acceso administrativo concedido.\n\n");
            return true;
        } else {
            printf("\nCredenciales incorrectas: Intente nuevamente.\n\n");
        }
    }
}