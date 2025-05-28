//Priscila Guzmán 9959-23-450
// Incluye el archivo de cabecera de la clase Usuario.
#include "Usuario.h"

// Librerías estándar para entrada/salida, manejo de archivos, teclado y cadenas de texto.
#include <iostream>
#include <fstream>
#include <conio.h>     // Para leer caracteres sin mostrar en pantalla (contraseña oculta).
#include <cstring>     // Para funciones como strncpy.
#include <cstdlib>     // Para usar system("cls") o system("clear").

// Incluye la clase Bitacora, usada para registrar eventos de login, registro, etc.
#include "Bitacora.h"

using namespace std;

// Instancia global de bitácora para registrar eventos relacionados con usuarios.
Bitacora bitacoralogUsuario;

// Define el nombre del archivo binario donde se almacenan los registros de usuario.
const string Usuario::ARCHIVO_LOGIN = "login.dat";

// Constructor por defecto: inicializa usuario y contraseña vacíos.
Usuario::Usuario() : nombreUsuario(""), contrasena("") {}

// Constructor que recibe nombre de usuario y contraseña.
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

// Establece el nombre del usuario activo (no confundir con el nombre de login).
void Usuario::setUsuario(const string& u) { usuario = u; }

// Devuelve el nombre de usuario (login).
string Usuario::getNombreUsuario() const { return nombreUsuario; }

// Devuelve la contraseña del usuario.
string Usuario::getContrasena() const { return contrasena; }

// Establece el nombre de usuario (login).
void Usuario::setNombreUsuario(const string& usuario) { nombreUsuario = usuario; }

// Establece la contraseña del usuario.
void Usuario::setContrasena(const string& contrasena) { this->contrasena = contrasena; }

// Limpia la pantalla de la consola dependiendo del sistema operativo.
void Usuario::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");   // En Windows
    #else
        system("clear"); // En Linux/macOS
    #endif
}

// Función para leer una contraseña sin mostrarla en pantalla.
string leerContrasenaOculta() {
    string contrasena;
    char tecla;
    while (true) {
        tecla = _getch(); // Lee carácter sin mostrarlo en pantalla.
        if (tecla == 13) break; // Enter (carácter 13) termina la entrada.
        else if (tecla == 8 && !contrasena.empty()) { // Retroceso
            contrasena.pop_back(); // Elimina último carácter
            cout << "\b \b";       // Borra el carácter en consola
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*'; // Muestra asterisco
        }
    }
    cout << endl;
    return contrasena;
}

// Autenticación de usuario
// Devuelve true si las credenciales coinciden, y guarda el nombre del usuario autenticado
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

// Permite registrar un nuevo usuario, escribiéndolo en el archivo binario
string Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n=== REGISTRO DE USUARIO ===";
    cout << "\nUsuario: ";
    cin >> nuevoUsuario;
    cout << "Contraseña: ";
    nuevaContrasena = leerContrasenaOculta();

    RegistroUsuario reg;
    // Copia los datos al registro, asegurando no exceder el tamaño del arreglo.
    strncpy(reg.nombreUsuario, nuevoUsuario.c_str(), sizeof(reg.nombreUsuario));
    strncpy(reg.contrasena, nuevaContrasena.c_str(), sizeof(reg.contrasena));

    ofstream archivo(ARCHIVO_LOGIN, ios::binary | ios::app); // Abre el archivo en modo binario, agregando al final.
    archivo.write(reinterpret_cast<const char*>(&reg), sizeof(RegistroUsuario)); // Escribe el nuevo registro.
    archivo.close();

    return nuevoUsuario;
}

// Pausa la ejecución del programa hasta que el usuario presione Enter.
void Usuario::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(); // Limpia buffer
    cin.get();    // Espera que se presione Enter
}

// Muestra el menú de autenticación y gestiona login, registro o salida.
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
                // Si se autentica correctamente, registra en bitácora y retorna true.
                if (autenticarDesdeArchivo(usuarioAutenticado)) {
                    bitacoralogUsuario.insertar(usuarioAutenticado, 1000, "Login", "Inicio exitoso");
                    return true;
                }
                // Si falla la autenticación, se registra intento fallido.
                bitacoralogUsuario.insertar("Desconocido", 1001, "Login", "Intento fallido");
                break;
            case 2: {
                // Registra un nuevo usuario y lo guarda en bitácora.
                string nuevo = registrarUsuario();
                bitacoralogUsuario.insertar(nuevo, 1002, "Login", "Usuario registrado");
                break;
            }
            case 3:
                // Sale del sistema de autenticación.
                return false;
            default:
                cout << "Opción inválida\n";
        }
    } while (true);
}
