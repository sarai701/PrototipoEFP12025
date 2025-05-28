//Priscila Guzmán 9959-23-450
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

class Bitacora {
public:
    struct RegistroBitacora {
        char usuario[30];
        int codigo;
        char aplicacion[30];
        char accion[50];
        char fechaHora[30];
    };

    void insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion);
    void mostrar();
    void menuBitacora();
};

#endif
