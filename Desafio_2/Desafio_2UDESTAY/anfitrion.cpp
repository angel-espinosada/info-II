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
