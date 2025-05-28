//Priscila Guzmán 9959-23-450
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

struct RegistroUsuario {
    char nombreUsuario[30];
    char contrasena[30];
};

class Usuario {
private:
    string usuario;
    string nombreUsuario;
    string contrasena;
    static const string ARCHIVO_LOGIN;

public:
    void setUsuario(const string& u);
    Usuario();
    Usuario(const string& usuario, const string& contrasena);
    string getNombreUsuario() const;
    string getContrasena() const;
    void setNombreUsuario(const string& usuario);
    void setContrasena(const string& contrasena);
    bool autenticarDesdeArchivo(string& usuarioAutenticado);
    string registrarUsuario();
    bool menuAutenticacion(string& usuarioAutenticado);
    static void limpiarPantalla();
    void pausar();
};

#endif
