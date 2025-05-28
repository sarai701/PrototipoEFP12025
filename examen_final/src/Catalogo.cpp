//Priscila Guzmán 9959-23-450
#include "Catalogo.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Bitacora.h"

using namespace std;

Bitacora bitacoralogCatalogo;

void Catalogo::setUsuario(const string& u) { usuario = u; }

void Catalogo::cargarProductos() {
    productos.clear();
    ifstream file(archivo, ios::binary); // Cambiado a 'file'
    if (!file) return;

    Producto p;
    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        productos.push_back(p);
    }
    file.close();
    ordenarProductos();
}

void Catalogo::guardarProductos() {
    ofstream file(archivo, ios::binary | ios::trunc); // Cambiado a 'file'
    for (const auto& p : productos) {
        file.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
    }
    file.close();
}

void Catalogo::ordenarProductos() {
    sort(productos.begin(), productos.end(), [](const Producto& a, const Producto& b) {
        return a.codigo < b.codigo;
    });
}

void Catalogo::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void Catalogo::menuCatalogo() {
    int opcion;
    do {
        cargarProductos();
        cout << "\n=== MENU CATALOGO ===" << endl;
        cout << "1. Crear Producto" << endl;
        cout << "2. Borrar Producto" << endl;
        cout << "3. Buscar Producto" << endl;
        cout << "4. Modificar Producto" << endl;
        cout << "5. Desplegar Productos" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearProducto(); break;
            case 2: borrarProducto(); break;
            case 3: buscarProducto(); break;
            case 4: modificarProducto(); break;
            case 5: desplegarProductos(); break;
            case 6: return;
            default: cout << "Opcion invalida." << endl;
        }
    } while (true);
}

void Catalogo::crearProducto() {
    Producto p;
    cout << "Codigo: ";
    cin.getline(p.codigo, sizeof(p.codigo));
    cout << "Nombre: ";
    cin.getline(p.nombre, sizeof(p.nombre));
    cout << "Precio: ";
    cin >> p.precio;
    cin.ignore();

    productos.push_back(p);
    guardarProductos();
    bitacoralogCatalogo.insertar(usuario, 2001, "Catalogo", "Crear Producto");
    cout << "Producto creado." << endl;
    pausar();
}


void Catalogo::borrarProducto() {
    char codigo[20];
    cout << "Codigo a borrar: ";
    cin.getline(codigo, sizeof(codigo));

    auto it = remove_if(productos.begin(), productos.end(), [&](const Producto& p) {
        return strcmp(p.codigo, codigo) == 0;
    });

    if (it != productos.end()) {
        productos.erase(it, productos.end());
        guardarProductos();
        bitacoralogCatalogo.insertar(usuario, 2002, "Catalogo", "Borrar Producto");
        cout << "Producto borrado." << endl;
    } else {
        cout << "No encontrado." << endl;
    }
    pausar();
}

void Catalogo::buscarProducto() {
    char codigo[20];
    cout << "Codigo a buscar: ";
    cin.getline(codigo, sizeof(codigo));

    for (const auto& p : productos) {
        if (strcmp(p.codigo, codigo) == 0) {
            cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre << ", Precio: " << p.precio << endl;
            bitacoralogCatalogo.insertar(usuario, 2003, "Catalogo", "Buscar Producto");
            pausar();
            return;
        }
    }
    cout << "No encontrado." << endl;
    pausar();
}

void Catalogo::modificarProducto() {
    char codigo[20];
    cout << "Codigo a modificar: ";
    cin.getline(codigo, sizeof(codigo));

    for (auto& p : productos) {
        if (strcmp(p.codigo, codigo) == 0) {
            cout << "Nuevo nombre: ";
            cin.getline(p.nombre, sizeof(p.nombre));
            cout << "Nuevo precio: ";
            cin >> p.precio;
            cin.ignore();
            guardarProductos();
            bitacoralogCatalogo.insertar(usuario, 2004, "Catalogo", "Modificar Producto");
            cout << "Producto modificado." << endl;
            pausar();
            return;
        }
    }
    cout << "No encontrado." << endl;
    pausar();
}

void Catalogo::desplegarProductos() {
    cout << "\n=== LISTA DE PRODUCTOS ===" << endl;
    for (const auto& p : productos) {
        cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre << ", Precio: " << p.precio << endl;
    }
    bitacoralogCatalogo.insertar(usuario, 2005, "Catalogo", "Desplegar Productos");
}
