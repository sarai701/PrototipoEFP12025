//Priscila Guzmán 9959-23-450
#include "Catalogo.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Bitacora.h"

using namespace std;

// Se declara una instancia global de Bitacora para registrar acciones del catálogo
Bitacora bitacoralogCatalogo;

// Método para establecer el nombre del usuario activo en el catálogo
void Catalogo::setUsuario(const string& u) {
    usuario = u;
}

// Carga los productos desde el archivo binario a la lista en memoria
void Catalogo::cargarProductos() {
    productos.clear();  // Limpia la lista antes de cargar nuevos datos.
    ifstream file(archivo, ios::binary); // Abre el archivo en modo binario.
    if (!file) return; // Si no se puede abrir, se sale.

    Producto p;
    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        productos.push_back(p); // Agrega cada producto leído al vector.
    }
    file.close();
    ordenarProductos(); // Ordena los productos por código.
}

// Guarda los productos actuales en memoria al archivo binario.
void Catalogo::guardarProductos() {
    ofstream file(archivo, ios::binary | ios::trunc); // Sobrescribe el archivo.
    for (const auto& p : productos) {
        file.write(reinterpret_cast<const char*>(&p), sizeof(Producto)); // Guarda cada producto.
    }
    file.close();
}

// Ordena los productos
void Catalogo::ordenarProductos() {
    sort(productos.begin(), productos.end(), [](const Producto& a, const Producto& b) {
        return a.codigo < b.codigo;
    });
}

// Pausa el programa hasta que el usuario presione Enter
void Catalogo::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Muestra el menú principal del catálogo con las opciones disponibles
void Catalogo::menuCatalogo() {
    int opcion;
    do {
        cargarProductos(); // Siempre carga los productos antes de mostrar el menú.

        cout << "\n=== MENU CATALOGO ===" << endl;
        cout << "1. Crear Producto" << endl;
        cout << "2. Borrar Producto" << endl;
        cout << "3. Buscar Producto" << endl;
        cout << "4. Modificar Producto" << endl;
        cout << "5. Desplegar Productos" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        cin.ignore(); // Elimina el salto de línea pendiente.

        switch (opcion) {
            case 1: crearProducto(); break;
            case 2: borrarProducto(); break;
            case 3: buscarProducto(); break;
            case 4: modificarProducto(); break;
            case 5: desplegarProductos(); break;
            case 6: return; // Sale del menú.
            default: cout << "Opcion invalida." << endl;
        }
    } while (true); // Bucle infinito hasta seleccionar Salir
}

// Crea un nuevo producto solicitando los datos al usuario.
void Catalogo::crearProducto() {
    Producto p;
    cout << "Codigo: ";
    cin.getline(p.codigo, sizeof(p.codigo));
    cout << "Nombre: ";
    cin.getline(p.nombre, sizeof(p.nombre));
    cout << "Precio: ";
    cin >> p.precio;
    cin.ignore();

    productos.push_back(p);   // Agrega el producto a la lista.
    guardarProductos();       // Guarda la lista en el archivo.
    bitacoralogCatalogo.insertar(usuario, 2001, "Catalogo", "Crear Producto"); // Registra en bitácora.
    cout << "Producto creado." << endl;
    pausar();
}

// Borra un producto según el código ingresado por el usuario.
void Catalogo::borrarProducto() {
    char codigo[20];
    cout << "Codigo a borrar: ";
    cin.getline(codigo, sizeof(codigo));

    // Busca el producto y lo elimina si existe.
    auto it = remove_if(productos.begin(), productos.end(), [&](const Producto& p) {
        return strcmp(p.codigo, codigo) == 0;
    });

    if (it != productos.end()) {
        productos.erase(it, productos.end()); // Elimina el producto.
        guardarProductos(); // Guarda la nueva lista.
        bitacoralogCatalogo.insertar(usuario, 2002, "Catalogo", "Borrar Producto"); // Bitácora.
        cout << "Producto borrado." << endl;
    } else {
        cout << "No encontrado." << endl;
    }
    pausar();
}

// Busca un producto y lo muestra si lo encuentra.
void Catalogo::buscarProducto() {
    char codigo[20];
    cout << "Codigo a buscar: ";
    cin.getline(codigo, sizeof(codigo));

    for (const auto& p : productos) {
        if (strcmp(p.codigo, codigo) == 0) {
            cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre << ", Precio: " << p.precio << endl;
            bitacoralogCatalogo.insertar(usuario, 2003, "Catalogo", "Buscar Producto"); // Bitácora.
            pausar();
            return;
        }
    }
    cout << "No encontrado." << endl;
    pausar();
}

// Modifica el nombre y precio de un producto existente.
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
            guardarProductos(); // Guarda los cambios.
            bitacoralogCatalogo.insertar(usuario, 2004, "Catalogo", "Modificar Producto"); // Bitácora.
            cout << "Producto modificado." << endl;
            pausar();
            return;
        }
    }
    cout << "No encontrado." << endl;
    pausar();
}

// Muestra todos los productos almacenados.
void Catalogo::desplegarProductos() {
    cout << "\n=== LISTA DE PRODUCTOS ===" << endl;
    for (const auto& p : productos) {
        cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre << ", Precio: " << p.precio << endl;
    }
    bitacoralogCatalogo.insertar(usuario, 2005, "Catalogo", "Desplegar Productos"); // Bitácora.
}
