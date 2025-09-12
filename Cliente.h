// Cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>

#define ARCHIVO_CLIENTES "Clientes.txt"
#define MAX_CEDULA 20
#define MAX_NOMBRE 100
#define MAX_TELEFONO 15

typedef struct {
    char *cedula;
    char *nombre;
    char *telefono;
} Cliente;

// Prototipos de funciones
// Proximamente...

#endif