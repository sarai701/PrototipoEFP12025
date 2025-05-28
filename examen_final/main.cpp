//Priscila Guzmán 9959-23-450
#include <iostream>
#include "Usuario.h"
#include "Catalogo.h"
#include "Bitacora.h"

using namespace std;


//Función que muestra el menú principal del sistema
void menuPrincipal(const string& usuario) {
    // Crea una instancia del catálogo para manejar los menús de catálogos.
    Catalogo catalogo;

    // Establece el nombre del usuario activo en la instancia del catálogo.
    catalogo.setUsuario(usuario);

    // Crea una instancia de la bitácora para mostrar los eventos del sistema.
    Bitacora bitacora;

    int opcion;

    // Bucle principal del menú que se repite hasta que el usuario seleccione salir.
    do {
        // Muestra el menú principal en pantalla.
        cout << "\n=== MENU GENERAL ===" << endl;
        cout << "Usuario: " << usuario << endl; // Muestra el usuario que ha iniciado sesión.
        cout << "1. Catalogos" << endl;
        cout << "2. Informes" << endl;
        cout << "3. Seguridad" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione: ";
        cin >> opcion;// Lee la opción seleccionada por el usuario.
        cin.ignore();// Limpia el buffer de entrada para evitar errores con cin.

        switch (opcion) {
            case 1:
                // Llama al menú de catálogos para mostrar submenús y operaciones relacionadas.
                catalogo.menuCatalogo();
                break;
            case 2:
                // Muestra un listado de productos
                catalogo.desplegarProductos();
                catalogo.pausar();
                break;
            case 3:
                // Muestra el contenido de la bitácora
                bitacora.mostrar();
                bitacora.menuBitacora();
                break;
            case 4:
                // Sale del sistema
                cout << "Saliendo..." << endl;
                return;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (true); // Repite el menú hasta que se seleccione la opción de salir
}


//Función principal del programa.

int main() {
    Usuario usuario; // Crea una instancia de la clase Usuario
    string usuarioAutenticado;// Variable para guardar el nombre del usuario que inicia sesión

    // Llama al menú de autenticación
    if (usuario.menuAutenticacion(usuarioAutenticado)) {
        menuPrincipal(usuarioAutenticado); // Llama al menú principal con el usuario autenticado.
    }

    return 0;
}
