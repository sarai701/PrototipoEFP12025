//Priscila Guzmán 9959-23-450
#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include "Bitacora.h"

using namespace std;

Bitacora bitacoralogUsuario;
const string Usuario::ARCHIVO_LOGIN = "login.dat";

Usuario::Usuario() : nombreUsuario(""), contrasena("") {}
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

void Usuario::setUsuario(const string& u) { usuario = u; }
string Usuario::getNombreUsuario() const { return nombreUsuario; }
string Usuario::getContrasena() const { return contrasena; }
void Usuario::setNombreUsuario(const string& usuario) { nombreUsuario = usuario; }
void Usuario::setContrasena(const string& contrasena) { this->contrasena = contrasena; }

void Usuario::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string leerContrasenaOculta() {
    string contrasena;
    char tecla;
    while (true) {
        tecla = _getch();
        if (tecla == 13) break;
        else if (tecla == 8 && !contrasena.empty()) {
            contrasena.pop_back();
            cout << "\b \b";
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*';
        }
    }
    cout << endl;
    return contrasena;
}

bool Usuario::autenticarDesdeArchivo(string& usuarioAutenticado) {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n=== INICIO DE SESION ===";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contraseña: ";
        contrasenaIngresada = leerContrasenaOculta();

        ifstream archivo(ARCHIVO_LOGIN, ios::binary);
        if (!archivo.is_open()) {
            cout << "\nError al abrir archivo\n";
            return false;
        }

        RegistroUsuario reg;
        while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(RegistroUsuario))) {
            if (usuarioIngresado == reg.nombreUsuario && contrasenaIngresada == reg.contrasena) {
                usuarioAutenticado = usuarioIngresado;
                archivo.close();
                return true;
            }
        }
        archivo.close();
        intentos--;
        cout << "\nCredenciales incorrectas. Intentos: " << intentos << endl;
    }
    return false;
}

string Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n=== REGISTRO DE USUARIO ===";
    cout << "\nUsuario: ";
    cin >> nuevoUsuario;
    cout << "Contraseña: ";
    nuevaContrasena = leerContrasenaOculta();

    RegistroUsuario reg;
    strncpy(reg.nombreUsuario, nuevoUsuario.c_str(), sizeof(reg.nombreUsuario));
    strncpy(reg.contrasena, nuevaContrasena.c_str(), sizeof(reg.contrasena));

    ofstream archivo(ARCHIVO_LOGIN, ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&reg), sizeof(RegistroUsuario));
    archivo.close();

    return nuevoUsuario;
}

void Usuario::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

bool Usuario::menuAutenticacion(string& usuarioAutenticado) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n=== SISTEMA DE ACCESO ===";
        cout << "\n1. Iniciar sesión";
        cout << "\n2. Registrar usuario";
        cout << "\n3. Salir";
        cout << "\nSeleccione: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (autenticarDesdeArchivo(usuarioAutenticado)) {
                    bitacoralogUsuario.insertar(usuarioAutenticado, 1000, "Login", "Inicio exitoso");
                    return true;
                }
                bitacoralogUsuario.insertar("Desconocido", 1001, "Login", "Intento fallido");
                break;
            case 2: {
                string nuevo = registrarUsuario();
                bitacoralogUsuario.insertar(nuevo, 1002, "Login", "Usuario registrado");
                break;
            }
            case 3:
                return false;
            default:
                cout << "Opción inválida\n";
        }
    } while (true);
}
