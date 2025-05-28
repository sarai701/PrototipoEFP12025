//Priscila Guzmán 9959-23-450
#include "Bitacora.h"

void Bitacora::insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion) {
    ofstream archivo("bitacora.dat", ios::binary | ios::app);
    if (!archivo.is_open()) return;

    RegistroBitacora registro;
    strncpy(registro.usuario, usuario.c_str(), sizeof(registro.usuario));
    registro.codigo = codigo;
    strncpy(registro.aplicacion, aplicacion.c_str(), sizeof(registro.aplicacion));
    strncpy(registro.accion, accion.c_str(), sizeof(registro.accion));

    time_t now = time(nullptr);
    char* fecha = ctime(&now);
    fecha[strcspn(fecha, "\n")] = '\0';
    strncpy(registro.fechaHora, fecha, sizeof(registro.fechaHora));

    archivo.write(reinterpret_cast<char*>(&registro), sizeof(registro));
    archivo.close();
}

void Bitacora::mostrar() {
    ifstream archivo("bitacora.dat", ios::binary);
    if (!archivo.is_open()) return;

    RegistroBitacora registro;
    cout << "\n=== BITACORA ===" << endl;
    while (archivo.read(reinterpret_cast<char*>(&registro), sizeof(registro))) {
        cout << "Usuario: " << registro.usuario
             << " | Codigo: " << registro.codigo
             << " | App: " << registro.aplicacion
             << " | Accion: " << registro.accion
             << " | Fecha: " << registro.fechaHora << endl;
    }
    archivo.close();
}

void Bitacora::menuBitacora() {
    int opcion;
    do {
        cout << "\n=== MENU BITACORA ===" << endl;
        cout << "1. Mostrar bitacora" << endl;
        cout << "2. Regresar" << endl;
        cout << "Seleccione: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                mostrar();
                break;
            case 2:
                return;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (true);
}
