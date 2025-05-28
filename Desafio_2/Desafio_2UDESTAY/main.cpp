#include <iostream>
#include "anfitrion.h"
#include <fstream>
#include <sstream>


using namespace std;


bool leerArchivoTexto(const string& nombreArchivo, string* &lineas, int &cantidadLineas);
bool filtroEliminarAnfitrion(const string& linea);
bool reescribirArchivoFiltrado(const string& nombreArchivo, bool (*filtro)(const string& linea));
bool filtroGenerico(const string& linea);
bool eliminarAnfitrionPorDocumento(const string& documento);

string documentoAEliminar = "";

int main()
{

    //Anfitrion a1("123456789", "Laura Restrepo", 15, 4.8);
   // a1.mostrarInfo();



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


/*

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


