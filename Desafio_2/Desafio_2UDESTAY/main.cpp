#include <iostream>
#include "anfitrion.h"
#include<reservacion.h>
#include <fstream>
#include <sstream>


using namespace std;
string obtenerNombreAnfitrion(const string& documento);
string obtenerNombreHuesped(const string& documento);

string documentoSesion = "";
bool leerArchivoTexto(const string& nombreArchivo, string* &lineas, int &cantidadLineas);
bool filtroEliminarAnfitrion(const string& linea);
bool reescribirArchivoFiltrado(const string& nombreArchivo, bool (*filtro)(const string& linea));
bool filtroGenerico(const string& linea);
bool eliminarAnfitrionPorDocumento(const string& documento);

string documentoAEliminar = "";

//Prototipo de funciones para el menu
// Prototipos del menú
void menuPrincipal();
void menuHuesped(const string& doc);
void menuAnfitrion(const string& doc);
bool iniciarSesion(const string& documento, const string& rol);


int main()
{
    menuPrincipal();

    //Anfitrion a1("123456789", "Laura Restrepo", 15, 4.8);
   // a1.mostrarInfo();


/*
    string* lineas = nullptr;
    int cantidad = 0;

    if (leerArchivoTexto("huespedes.txt", lineas, cantidad)) {
        cout << "\nContenido del archivo anfitriones.txt:\n";
        for (int i = 0; i < cantidad; ++i)
            cout << "Línea " << i + 1 << ": " << lineas[i] << endl;
        delete[] lineas;
    } else {
        cout << "Error al leer el archivo.\n";
    }




    string doc;
    cout << "\nIngrese el documento del anfitrión a eliminar: ";
    cin >> doc;

    if (eliminarAnfitrionPorDocumento(doc)) {
        cout << "Anfitrión eliminado exitosamente.\n";
    } else {
        cout << "No se pudo eliminar el anfitrión.\n";
    }
*/
    return 0;





}

bool leerArchivoTexto(const string& nombreArchivo, string* &lineas, int &cantidadLineas) {
    ifstream in(nombreArchivo);
    if (!in.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return false;
    }

    // Primero contamos cuántas líneas hay
    string temp;
    int total = 0;
    while (getline(in, temp)) total++;

    // Volvemos al inicio del archivo para leer de nuevo
    in.clear();
    in.seekg(0);

    // Reservamos memoria dinámica
    lineas = new string[total];
    cantidadLineas = 0;

    // Leemos línea por línea y las guardamos
    while (getline(in, temp)) {
        if (cantidadLineas < total) {
            lineas[cantidadLineas++] = temp;
        } else {
            cout << "Advertencia: se leyó más de lo esperado.\n";
            break;
        }
    }

    in.close();
    return true;
}

bool reescribirArchivoFiltrado(
    const string& nombreArchivo,
    bool (*filtro)(const string& linea)
    ) {
    string* lineas = nullptr;
    int cantidad = 0;

    if (!leerArchivoTexto(nombreArchivo, lineas, cantidad)) {
        return false;
    }

    ofstream out("temp.txt");
    if (!out.is_open()) {
        delete[] lineas;
        return false;
    }

    for (int i = 0; i < cantidad; ++i) {
        if (filtro(lineas[i])) {
            out << lineas[i] << endl;
        }
    }

    out.close();
    delete[] lineas;

    // Reemplazar archivo original
    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());

    return true;
}


bool filtroGenerico(const string& linea) {
    return linea.substr(0, documentoAEliminar.length()) != documentoAEliminar;
}
bool eliminarAnfitrionPorDocumento(const string& documento) {
    documentoAEliminar = documento;  // guardar el documento deseado
    return reescribirArchivoFiltrado("anfitriones.txt", filtroGenerico);
}

//Funciones del menu
// Menú principal
void menuPrincipal() {
    int opcion;
    string documento;

    do {
        cout << "\n=== BIENVENIDO A UDESTAY ===\n";
        cout << "1. Iniciar sesion como huesped\n";
        cout << "2. Iniciar sesion como anfitrion\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese su numero de documento: ";
            cin >> documento;
            if (iniciarSesion(documento, "huesped")) {
                menuHuesped(documento);
            } else {
                cout << "Credenciales invalidas.\n";
            }
            break;
        case 2:
            cout << "Ingrese su numero de documento: ";
            cin >> documento;
            if (iniciarSesion(documento, "anfitrion")) {
                menuAnfitrion(documento);
            } else {
                cout << "Credenciales invalidas.\n";
            }
            break;
        case 0:
            cout << "Saliendo del sistema.\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);
}

// Menú para huesped
void menuHuesped(const string& doc) {
    int opcion;
    do {
        cout << "\n=== MENU HUESPED ===\n";
        cout << "Bienvenido, " << obtenerNombreHuesped(documentoSesion) << endl;
        cout << "1. Reservar alojamiento\n";
        cout << "2. Buscar alojamiento por codigo\n";
        cout << "3. Anular reservacion\n";
        cout << "4. Ver mis reservas activas\n";
        cout << "0. Cerrar sesion\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            Reservacion r;
            r.buscarAlojamientosDisponibles();
            break;
        }
        case 2:
            cout << "TODO: buscarAlojamientoPorCodigo()\n";
            break;
        case 3:
            cout << "TODO: anularReservacion()\n";
            break;
        case 4: {
            Reservacion r;
            r.verReservasHuesped(documentoSesion);  // documentoSesion = documento actual del huésped
            break;
        }

        case 0:
            cout << "Sesion cerrada.\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

// Menú para anfitrión
void menuAnfitrion(const string& doc) {
    int opcion;
    do {
        cout << "\n=== MENU ANFITRION ===\n";
        cout << "Bienvenido, " << obtenerNombreAnfitrion(documentoSesion) << endl;

        cout << "1. Ver mis reservaciones\n";
        cout << "2. Anular reservacion\n";
        cout << "3. Actualizar historico\n";
        cout << "4. Medicion de recursos\n";
        cout << "0. Cerrar sesion\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            Reservacion r;
            r.verReservacionesAnfitrion(documentoSesion);
            break;
        }

        case 2: {
            Reservacion r;
            r.anularReservacion(doc);
            break;
        }
        case 3: {
            Reservacion r;
            r.actualizarHistorico();
            break;
        }

        case 4:
            cout << "TODO: medirConsumoRecursos()\n";
            break;
        case 0:
            cout << "Sesion cerrada.\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

// Verifica si existe el documento en el archivo correspondiente
bool iniciarSesion(const string& documento, const string& rol) {
    string* lineas = nullptr;
    int cantidad = 0;
    string archivo = (rol == "huesped") ? "huespedes.txt" : "anfitriones.txt";

    if (leerArchivoTexto(archivo, lineas, cantidad)) {
        for (int i = 0; i < cantidad; ++i) {
            if (lineas[i].substr(0, documento.size()) == documento) {
                documentoSesion = documento;
                delete[] lineas;
                return true;
            }
        }
        delete[] lineas;
    }
    return false;
}
string obtenerNombreAnfitrion(const string& documento) {
    string* lineas = nullptr;
    int cantidad = 0;
    if (leerArchivoTexto("anfitriones.txt", lineas, cantidad)) {
        for (int i = 0; i < cantidad; ++i) {
            if (lineas[i].substr(0, documento.length()) == documento) {
                size_t pos1 = lineas[i].find('-');
                size_t pos2 = lineas[i].find('-', pos1 + 1);
                string nombre = lineas[i].substr(pos1 + 1, pos2 - pos1 - 1);
                delete[] lineas;
                return nombre;
            }
        }
        delete[] lineas;
    }
    return "Anfitrión desconocido";
}

string obtenerNombreHuesped(const string& documento) {
    string* lineas = nullptr;
    int cantidad = 0;
    if (leerArchivoTexto("huespedes.txt", lineas, cantidad)) {
        for (int i = 0; i < cantidad; ++i) {
            if (lineas[i].substr(0, documento.length()) == documento) {
                size_t pos1 = lineas[i].find('-');
                size_t pos2 = lineas[i].find('-', pos1 + 1);
                string nombre = lineas[i].substr(pos1 + 1, pos2 - pos1 - 1);
                delete[] lineas;
                return nombre;
            }
        }
        delete[] lineas;
    }
    return "Anfitrión desconocido";
}
