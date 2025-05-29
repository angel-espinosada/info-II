#include "anfitrion.h"
#include <iostream>
#include <sstream>

using namespace std;
// Esto le dice al compilador: "esta función está en otro lado"
extern bool leerArchivoTexto(const string& nombreArchivo, string* &lineas, int &cantidadLineas);

// ------------------ Constructores ------------------

Anfitrion::Anfitrion() {
    alojamientos = nullptr;
    cantidadAlojamientos = 0;
}

Anfitrion::Anfitrion(string doc, string nombre, int antiguedad, float punt) {
    this->numeroDocumento = doc;
    this->nombre = nombre;
    this->antiguedadMeses = antiguedad;
    this->puntuacion = punt;
    alojamientos = nullptr;
    cantidadAlojamientos = 0;
}

Anfitrion::Anfitrion(const Anfitrion& otro) {
    numeroDocumento = otro.numeroDocumento;
    nombre = otro.nombre;
    antiguedadMeses = otro.antiguedadMeses;
    puntuacion = otro.puntuacion;
    cantidadAlojamientos = otro.cantidadAlojamientos;

    if (cantidadAlojamientos > 0) {
        alojamientos = new string[cantidadAlojamientos];
        for (int i = 0; i < cantidadAlojamientos; ++i)
            alojamientos[i] = otro.alojamientos[i];
    } else {
        alojamientos = nullptr;
    }
}

// ------------------ Destructor ------------------

Anfitrion::~Anfitrion() {
    delete[] alojamientos;
}

// ------------------ Operador de asignación ------------------

Anfitrion& Anfitrion::operator=(const Anfitrion& otro) {
    if (this != &otro) {
        delete[] alojamientos;

        numeroDocumento = otro.numeroDocumento;
        nombre = otro.nombre;
        antiguedadMeses = otro.antiguedadMeses;
        puntuacion = otro.puntuacion;
        cantidadAlojamientos = otro.cantidadAlojamientos;

        if (cantidadAlojamientos > 0) {
            alojamientos = new string[cantidadAlojamientos];
            for (int i = 0; i < cantidadAlojamientos; ++i)
                alojamientos[i] = otro.alojamientos[i];
        } else {
            alojamientos = nullptr;
        }
    }
    return *this;
}

// ------------------ Getters ------------------

string Anfitrion::getNumeroDocumento() {
    return numeroDocumento;
}

string Anfitrion::getNombre() {
    return nombre;
}

int Anfitrion::getAntiguedad() {
    return antiguedadMeses;
}

float Anfitrion::getPuntuacion() {
    return puntuacion;
}

int Anfitrion::getCantidadAlojamientos() {
    return cantidadAlojamientos;
}

string Anfitrion::getAlojamiento(int i) {
    if (i >= 0 && i < cantidadAlojamientos)
        return alojamientos[i];
    return "";
}

// ------------------ Setters ------------------

void Anfitrion::setNombre(string nuevoNombre) {
    nombre = nuevoNombre;
}

void Anfitrion::setAntiguedad(int meses) {
    antiguedadMeses = meses;
}

void Anfitrion::setPuntuacion(float nuevaPuntuacion) {
    puntuacion = nuevaPuntuacion;
}

void Anfitrion::setAlojamientos(string* lista, int cantidad) {
    delete[] alojamientos;
    cantidadAlojamientos = cantidad;
    alojamientos = new string[cantidad];
    for (int i = 0; i < cantidad; ++i)
        alojamientos[i] = lista[i];
}

// ------------------ Utilidades ------------------

void Anfitrion::mostrarInfo() {
    cout << "Anfitrión: " << nombre << " (" << numeroDocumento << ")\n";
    cout << "Antigüedad: " << antiguedadMeses << " meses | Puntuación: " << puntuacion << "\n";
    if (cantidadAlojamientos > 0) {
        cout << "Alojamientos: ";
        for (int i = 0; i < cantidadAlojamientos; ++i)
            cout << alojamientos[i] << (i < cantidadAlojamientos - 1 ? ", " : "");
        cout << "\n";
    } else {
        cout << "Sin alojamientos.\n";
    }
}

string Anfitrion::toTexto() const {
    string texto = numeroDocumento + "-" + nombre + "-" + to_string(antiguedadMeses) + "-" + to_string(puntuacion);
    if (cantidadAlojamientos > 0) {
        texto += "-";
        for (int i = 0; i < cantidadAlojamientos; ++i) {
            texto += alojamientos[i];
            if (i < cantidadAlojamientos - 1)
                texto += ",";
        }
    }
    return texto;
}

Anfitrion* Anfitrion::cargarDesdeArchivo(const string& nombreArchivo, int& cantidad) {
    string* lineas = nullptr;
    if (!leerArchivoTexto(nombreArchivo, lineas, cantidad)) {
        cantidad = 0;
        return nullptr;
    }

    Anfitrion* lista = new Anfitrion[cantidad];

    for (int i = 0; i < cantidad; ++i) {
        stringstream ss(lineas[i]);
        string doc, nom, antigStr, puntStr, alojStr;

        getline(ss, doc, '-');
        getline(ss, nom, '-');
        getline(ss, antigStr, '-');
        getline(ss, puntStr, '-');
        getline(ss, alojStr);  // puede estar vacío

        lista[i].numeroDocumento = doc;
        lista[i].nombre = nom;
        lista[i].antiguedadMeses = stoi(antigStr);
        lista[i].puntuacion = stof(puntStr);

        if (!alojStr.empty()) {
            stringstream alojSS(alojStr);
            string cod;
            string temp[20];
            int cont = 0;
            while (getline(alojSS, cod, ',')) {
                temp[cont++] = cod;
            }
            lista[i].setAlojamientos(temp, cont);
        } else {
            lista[i].setAlojamientos(nullptr, 0);
        }
    }

    delete[] lineas;
    return lista;
}
void medirConsumoRecursos() {
    string* alojamientos = nullptr;
    int cantAlojamientos = 0;

    string* anfitriones = nullptr;
    int cantAnfitriones = 0;

    string* reservas = nullptr;
    int cantReservas = 0;

    size_t memoriaTotal = 0;
    int totalIteraciones = 0;

    // Leer archivos
    if (!leerArchivoTexto("alojamientos.txt", alojamientos, cantAlojamientos)) {
        cout << "Error leyendo alojamientos.txt\n";
        return;
    }

    if (!leerArchivoTexto("anfitriones.txt", anfitriones, cantAnfitriones)) {
        cout << "Error leyendo anfitriones.txt\n";
        delete[] alojamientos;
        return;
    }

    if (!leerArchivoTexto("reservas.txt", reservas, cantReservas)) {
        cout << "Error leyendo reservas.txt\n";
        delete[] alojamientos;
        delete[] anfitriones;
        return;
    }

    // Calcular memoria usada y contar iteraciones
    for (int i = 0; i < cantAlojamientos; ++i) {
        memoriaTotal += alojamientos[i].size();
        totalIteraciones++;
    }

    for (int i = 0; i < cantAnfitriones; ++i) {
        memoriaTotal += anfitriones[i].size();
        totalIteraciones++;
    }

    for (int i = 0; i < cantReservas; ++i) {
        memoriaTotal += reservas[i].size();
        totalIteraciones++;
    }

    // Resultados
    cout << "\n=== CONSUMO DE RECURSOS ===\n";
    cout << "Cantidad de alojamientos: " << cantAlojamientos << endl;
    cout << "Cantidad de anfitriones: " << cantAnfitriones << endl;
    cout << "Cantidad de reservas: " << cantReservas << endl;
    cout << "Iteraciones totales: " << totalIteraciones << endl;
    cout << "Memoria total estimada: " << memoriaTotal << " bytes ("
         << memoriaTotal / 1024.0 << " KB)" << endl;

    // Liberar memoria
    delete[] alojamientos;
    delete[] anfitriones;
    delete[] reservas;
}
