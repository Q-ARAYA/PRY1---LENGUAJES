#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>

extern char* espacioDeMemoria();

Cliente CrearCliente() {
    Cliente cli;
    cli.cedula = NULL;
    cli.nombre = NULL;
    cli.telefono = NULL;
    return cli;
}

bool validarCedulaUnica(const char* cedula) {
    FILE *archi = fopen(ARCHIVO_CLIENTES, "r");
    if (!archi) return true; // Si no existe archivo, la cédula es única
    
    char linea[100];
    char cedulaArchivo[20];
    bool esUnica = true;
    
    while (fgets(linea, sizeof(linea), archi)) {
        if (sscanf(linea, "Cedula: %19s", cedulaArchivo) == 1) {
            int i = 0;
            while (cedula[i] != '\0' && cedulaArchivo[i] != '\0') {
                if (cedula[i] != cedulaArchivo[i]) break;
                i++;
            }
            if (cedula[i] == '\0' && cedulaArchivo[i] == '\0') {
                esUnica = false;
                break;
            }
        }
    }

    fclose(archi);
    return esUnica;
}

bool validarTelefono(const char* telefono) {
    int longitud = 0;
    while (telefono[longitud] != '\0') longitud++;
    
    if (longitud < 8) return false;
    
    for (int i = 0; i < longitud; i++) {
        if (telefono[i] < '0' || telefono[i] > '9') return false;
    }
    return true;
}

void registrarCliente() {
    Cliente cli = CrearCliente();
    int intentos = 0;
    
    // Solicitar cédula
    do {
        if (intentos > 0) {
            printf("Cedula no valida o ya existe. Intente nuevamente.\n");
            free(cli.cedula);
        }
        
        printf("Cedula: ");
        cli.cedula = espacioDeMemoria();
        intentos++;
        
    } while (!validarCedulaUnica(cli.cedula));
    
    // Solicitar nombre
    printf("Nombre: ");
    cli.nombre = espacioDeMemoria();
    
    // Solicitar teléfono
    intentos = 0;
    do {
        if (intentos > 0) {
            printf("Telefono invalido. Debe tener solo digitos y minimo 8 caracteres.\n");
            free(cli.telefono);
        }
        
        printf("Telefono: ");
        cli.telefono = espacioDeMemoria();
        intentos++;
        
    } while (!validarTelefono(cli.telefono));
    
    // Guardar en archivo
    guardarClienteEnTXT(&cli);
    
    // Liberar memoria
    LiberarMemoriaCliente(&cli);
}

void guardarClienteEnTXT(Cliente *cli) {
    FILE *archi = fopen(ARCHIVO_CLIENTES, "a");
    if (!archi) {
        perror("No se pudo abrir el archivo de clientes");
        return;
    }
    
    fprintf(archi, "Cedula: %s\n", cli->cedula);
    fprintf(archi, "Nombre: %s\n", cli->nombre);
    fprintf(archi, "Telefono: %s\n", cli->telefono);
    fprintf(archi, ";\n");
    
    fclose(archi);
    printf("\nCliente registrado exitosamente!\n\n");
}

void LiberarMemoriaCliente(Cliente *cli) {
    free(cli->cedula);
    free(cli->nombre);
    free(cli->telefono);
    cli->cedula = NULL;
    cli->nombre = NULL;
    cli->telefono = NULL;
}