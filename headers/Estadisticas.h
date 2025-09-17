#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Pedido.h"
#include "Libro.h"

typedef struct {
    char *cedula;   // Puntero dinámico para la cédula
    char *nombre;   // Puntero dinámico para el nombre
    int pedidos;    // Contador de pedidos
} ClienteEstadistica;

typedef struct {
    int codigo;
    char *nombre;  
    int vendidos;
} LibroEstadistica;


void calcularTotalVentas();
void clientesConMasPedidos();
void librosMasVendidos();

#endif