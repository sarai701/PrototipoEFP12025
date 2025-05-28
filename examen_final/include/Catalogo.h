//Priscila Guzmán 9959-23-450
#ifndef CATALOGO_H
#define CATALOGO_H

#include <string>
#include <vector>
#include "Bitacora.h"

using namespace std;

class Catalogo {
private:
    struct Producto {
    char codigo[20];
    char nombre[50];
    double precio;
};

    vector<Producto> productos;
    string usuario;
    string archivo = "productos.dat";

    void cargarProductos();
    void guardarProductos();
    void ordenarProductos();

public:
    void setUsuario(const string& u);
    void menuCatalogo();
    void crearProducto();
    void borrarProducto();
    void buscarProducto();
    void modificarProducto();
    void desplegarProductos();
    void pausar();
};

#endif
