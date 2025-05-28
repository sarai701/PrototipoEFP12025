//Priscila Guzm�n 9959-23-450
#include <iostream>
#include "Usuario.h"
#include "Catalogo.h"
#include "Bitacora.h"

using namespace std;


//Funci�n que muestra el men� principal del sistema
void menuPrincipal(const string& usuario) {
    // Crea una instancia del cat�logo para manejar los men�s de cat�logos.
    Catalogo catalogo;

    // Establece el nombre del usuario activo en la instancia del cat�logo.
    catalogo.setUsuario(usuario);

    // Crea una instancia de la bit�cora para mostrar los eventos del sistema.
    Bitacora bitacora;

    int opcion;

    // Bucle principal del men� que se repite hasta que el usuario seleccione salir.
    do {
        // Muestra el men� principal en pantalla.
        cout << "\n=== MENU GENERAL ===" << endl;
        cout << "Usuario: " << usuario << endl; // Muestra el usuario que ha iniciado sesi�n.
        cout << "1. Catalogos" << endl;
        cout << "2. Informes" << endl;
        cout << "3. Seguridad" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione: ";
        cin >> opcion;// Lee la opci�n seleccionada por el usuario.
        cin.ignore();// Limpia el buffer de entrada para evitar errores con cin.

        switch (opcion) {
            case 1:
                // Llama al men� de cat�logos para mostrar submen�s y operaciones relacionadas.
                catalogo.menuCatalogo();
                break;
            case 2:
                // Muestra un listado de productos
                catalogo.desplegarProductos();
                catalogo.pausar();
                break;
            case 3:
                // Muestra el contenido de la bit�cora
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
    } while (true); // Repite el men� hasta que se seleccione la opci�n de salir
}


//Funci�n principal del programa.

int main() {
    Usuario usuario; // Crea una instancia de la clase Usuario
    string usuarioAutenticado;// Variable para guardar el nombre del usuario que inicia sesi�n

    // Llama al men� de autenticaci�n
    if (usuario.menuAutenticacion(usuarioAutenticado)) {
        menuPrincipal(usuarioAutenticado); // Llama al men� principal con el usuario autenticado.
    }

    return 0;
}
