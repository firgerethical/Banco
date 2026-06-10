#include <iostream>
#include <cstring>
#include <cstdio>


#ifdef _WIN32
#include <windows.h>
#endif

#include "include/estructuras.h"
#include "include/lista_cuentas.h"
#include "include/pila.h"
#include "include/cola.h"
#include "include/archivos.h"
#include "include/administrador.h"
#include "include/usuario.h"


NodoCuenta* listaCuentas = nullptr;
NodoPila*   pilaSesion   = nullptr;
float       saldoCajero  = SALDO_INICIAL_CAJERO;
int         contadorTx   = 0;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "╔══════════════════════════════╗\n"
              << "║     BANCO AUTOCAJERO         ║\n"
              << "╚══════════════════════════════╝\n\n";

    cargarCasosPrueba(listaCuentas, "casosPrueba.txt");

    int rol;
    do {
        std::cout << "\n╔══════════════════════════════╗\n"
                  << "║       MENU PRINCIPAL         ║\n"
                  << "╠══════════════════════════════╣\n"
                  << "║  1. Administrador            ║\n"
                  << "║  2. Usuario (cajero)         ║\n"
                  << "║  0. Salir                    ║\n"
                  << "╚══════════════════════════════╝\n"
                  << "  Opcion: ";
        std::cin >> rol;

        switch (rol) {
            case 1:
                menuAdministrador(listaCuentas, saldoCajero);
                break;
            case 2:
                menuUsuario(listaCuentas, pilaSesion, saldoCajero, contadorTx);
                break;
            case 0:
                // Solo genera resumen si el usuario no cerro sesion explicitamente
                if (!pilaVacia(pilaSesion)) {
                    generarResumenSesion(pilaSesion, "sesion_sin_cerrar", "resumenSesion.txt");
                    liberarPila(pilaSesion);   // evita doble guardado
                }
                std::cout << "  Hasta luego.\n";
                break;
            default:
                std::cout << "  Opcion invalida.\n";
        }
    } while (rol != 0);

    liberarPila(pilaSesion);
    liberarLista(listaCuentas);
    return 0;
}
