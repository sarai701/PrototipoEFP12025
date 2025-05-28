//Priscila Guzm�n 9959-23-450
#include "Bitacora.h"

// M�todo para insertar un registro en la bit�cora
// Recibe el nombre del usuario, un c�digo num�rico, el nombre de la aplicaci�n y la acci�n realizada
void Bitacora::insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion) {
    // Abre el archivo de bit�cora en modo binario y de escritura, agregando al final del archivo.
    ofstream archivo("bitacora.dat", ios::binary | ios::app);
    if (!archivo.is_open()) return; // Si no se puede abrir, se sale de la funci�n.

    RegistroBitacora registro; // Estructura para almacenar los datos del registro.

    // Copia los datos al registro, asegurando que no excedan el tama�o del arreglo.
    strncpy(registro.usuario, usuario.c_str(), sizeof(registro.usuario));
    registro.codigo = codigo;
    strncpy(registro.aplicacion, aplicacion.c_str(), sizeof(registro.aplicacion));
    strncpy(registro.accion, accion.c_str(), sizeof(registro.accion));

    // Obtiene la fecha y hora actual del sistema
    time_t now = time(nullptr);             // Obtiene el tiempo actual
    char* fecha = ctime(&now);              // Lo convierte a una cadena legible
    fecha[strcspn(fecha, "\n")] = '\0';
    strncpy(registro.fechaHora, fecha, sizeof(registro.fechaHora));//Registra fecha y hora

    // Escribe el registro en el archivo.
    archivo.write(reinterpret_cast<char*>(&registro), sizeof(registro));
    archivo.close(); // Cierra el archivo
}

// M�todo que muestra todos los registros almacenados en la bit�cora.
void Bitacora::mostrar() {
    // Abre el archivo de bit�cora en modo binario de solo lectura.
    ifstream archivo("bitacora.dat", ios::binary);
    if (!archivo.is_open()) return; // Si no se puede abrir, se sale de la funci�n.

    RegistroBitacora registro; // Estructura para leer los registros.
    cout << "\n=== BITACORA ===" << endl;

    // Lee y muestra todos los registros del archivo.
    while (archivo.read(reinterpret_cast<char*>(&registro), sizeof(registro))) {
        cout << "Usuario: " << registro.usuario
             << " | Codigo: " << registro.codigo
             << " | App: " << registro.aplicacion
             << " | Accion: " << registro.accion
             << " | Fecha: " << registro.fechaHora << endl;
    }

    archivo.close(); // Cierra el archivo.
}

// Muestra un men� interactivo para visualizar la bit�cora.
void Bitacora::menuBitacora() {
    int opcion; // Variable para almacenar la opci�n del usuario.
    do {
        // Muestra el men� principal de bit�cora.
        cout << "\n=== MENU BITACORA ===" << endl;
        cout << "1. Mostrar bitacora" << endl;
        cout << "2. Regresar" << endl;
        cout << "Seleccione: ";
        cin >> opcion;

        // Manejo de errores por entrada no v�lida.
        if (cin.fail()) {
            cin.clear();               // Limpia el estado de error.
            cin.ignore(10000, '\n');   // Descarta los caracteres inv�lidos del b�fer.
            opcion = 0;                // Opci�n inv�lida para activar el mensaje.
        }

        // Eval�a la opci�n seleccionada.
        switch (opcion) {
            case 1:
                mostrar(); // Muestra todos los registros.
                break;
            case 2:
                return;    // Sale del men�.
            default:
                cout << "Opcion invalida." << endl; // Opci�n no reconocida.
        }
    } while (true); // Repite el men� hasta que el usuario elija regresar.
}
