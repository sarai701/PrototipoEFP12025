//Priscila Guzm�n 9959-23-450
// Incluye el archivo de cabecera de la clase Usuario.
#include "Usuario.h"

// Librer�as est�ndar para entrada/salida, manejo de archivos, teclado y cadenas de texto.
#include <iostream>
#include <fstream>
#include <conio.h>     // Para leer caracteres sin mostrar en pantalla (contrase�a oculta).
#include <cstring>     // Para funciones como strncpy.
#include <cstdlib>     // Para usar system("cls") o system("clear").

// Incluye la clase Bitacora, usada para registrar eventos de login, registro, etc.
#include "Bitacora.h"

using namespace std;

// Instancia global de bit�cora para registrar eventos relacionados con usuarios.
Bitacora bitacoralogUsuario;

// Define el nombre del archivo binario donde se almacenan los registros de usuario.
const string Usuario::ARCHIVO_LOGIN = "login.dat";

// Constructor por defecto: inicializa usuario y contrase�a vac�os.
Usuario::Usuario() : nombreUsuario(""), contrasena("") {}

// Constructor que recibe nombre de usuario y contrase�a.
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

// Establece el nombre del usuario activo (no confundir con el nombre de login).
void Usuario::setUsuario(const string& u) { usuario = u; }

// Devuelve el nombre de usuario (login).
string Usuario::getNombreUsuario() const { return nombreUsuario; }

// Devuelve la contrase�a del usuario.
string Usuario::getContrasena() const { return contrasena; }

// Establece el nombre de usuario (login).
void Usuario::setNombreUsuario(const string& usuario) { nombreUsuario = usuario; }

// Establece la contrase�a del usuario.
void Usuario::setContrasena(const string& contrasena) { this->contrasena = contrasena; }

// Limpia la pantalla de la consola dependiendo del sistema operativo.
void Usuario::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");   // En Windows
    #else
        system("clear"); // En Linux/macOS
    #endif
}

// Funci�n para leer una contrase�a sin mostrarla en pantalla.
string leerContrasenaOculta() {
    string contrasena;
    char tecla;
    while (true) {
        tecla = _getch(); // Lee car�cter sin mostrarlo en pantalla.
        if (tecla == 13) break; // Enter (car�cter 13) termina la entrada.
        else if (tecla == 8 && !contrasena.empty()) { // Retroceso
            contrasena.pop_back(); // Elimina �ltimo car�cter
            cout << "\b \b";       // Borra el car�cter en consola
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*'; // Muestra asterisco
        }
    }
    cout << endl;
    return contrasena;
}

// Autenticaci�n de usuario
// Devuelve true si las credenciales coinciden, y guarda el nombre del usuario autenticado
bool Usuario::autenticarDesdeArchivo(string& usuarioAutenticado) {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n=== INICIO DE SESION ===";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contrase�a: ";
        contrasenaIngresada = leerContrasenaOculta();

        ifstream archivo(ARCHIVO_LOGIN, ios::binary);
        if (!archivo.is_open()) {
            cout << "\nError al abrir archivo\n";
            return false;
        }

        RegistroUsuario reg;
        // Lee cada registro del archivo hasta encontrar coincidencia
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

// Permite registrar un nuevo usuario, escribi�ndolo en el archivo binario
string Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n=== REGISTRO DE USUARIO ===";
    cout << "\nUsuario: ";
    cin >> nuevoUsuario;
    cout << "Contrase�a: ";
    nuevaContrasena = leerContrasenaOculta();

    RegistroUsuario reg;
    // Copia los datos al registro, asegurando no exceder el tama�o del arreglo.
    strncpy(reg.nombreUsuario, nuevoUsuario.c_str(), sizeof(reg.nombreUsuario));
    strncpy(reg.contrasena, nuevaContrasena.c_str(), sizeof(reg.contrasena));

    ofstream archivo(ARCHIVO_LOGIN, ios::binary | ios::app); // Abre el archivo en modo binario, agregando al final.
    archivo.write(reinterpret_cast<const char*>(&reg), sizeof(RegistroUsuario)); // Escribe el nuevo registro.
    archivo.close();

    return nuevoUsuario;
}

// Pausa la ejecuci�n del programa hasta que el usuario presione Enter.
void Usuario::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(); // Limpia buffer
    cin.get();    // Espera que se presione Enter
}

// Muestra el men� de autenticaci�n y gestiona login, registro o salida.
bool Usuario::menuAutenticacion(string& usuarioAutenticado) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n=== SISTEMA DE ACCESO ===";
        cout << "\n1. Iniciar sesi�n";
        cout << "\n2. Registrar usuario";
        cout << "\n3. Salir";
        cout << "\nSeleccione: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Si se autentica correctamente, registra en bit�cora y retorna true.
                if (autenticarDesdeArchivo(usuarioAutenticado)) {
                    bitacoralogUsuario.insertar(usuarioAutenticado, 1000, "Login", "Inicio exitoso");
                    return true;
                }
                // Si falla la autenticaci�n, se registra intento fallido.
                bitacoralogUsuario.insertar("Desconocido", 1001, "Login", "Intento fallido");
                break;
            case 2: {
                // Registra un nuevo usuario y lo guarda en bit�cora.
                string nuevo = registrarUsuario();
                bitacoralogUsuario.insertar(nuevo, 1002, "Login", "Usuario registrado");
                break;
            }
            case 3:
                // Sale del sistema de autenticaci�n.
                return false;
            default:
                cout << "Opci�n inv�lida\n";
        }
    } while (true);
}
