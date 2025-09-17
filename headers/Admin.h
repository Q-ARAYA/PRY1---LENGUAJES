#ifndef ADMIN_H
#define ADMIN_H

#include <stdbool.h>

#define ARCHIVO_CREDENCIALES "data/Admin.txt"

// Prototipos de funciones
bool verificarCredenciales();
bool autenticarAdministrativo();

#endif