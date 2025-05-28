#include "huesped.h"
#include <iostream>

Huesped::Huesped() : reservas(nullptr), cantidadReservas(0) {}

Huesped::Huesped(string doc, string nom, int ant, float punt)
    : documento(doc), nombre(nom), antiguedadMeses(ant), puntuacion(punt), reservas(nullptr), cantidadReservas(0) {}

Huesped::Huesped(const Huesped& otro) {
    documento = otro.documento;
    nombre = otro.nombre;
    antiguedadMeses = otro.antiguedadMeses;
    puntuacion = otro.puntuacion;
    cantidadReservas = otro.cantidadReservas;

    if (cantidadReservas > 0) {
        reservas = new string[cantidadReservas];
        for (int i = 0; i < cantidadReservas; ++i)
            reservas[i] = otro.reservas[i];
    } else {
        reservas = nullptr;
    }
}

Huesped::~Huesped() {
    delete[] reservas;
}

Huesped& Huesped::operator=(const Huesped& otro) {
    if (this != &otro) {
        delete[] reservas;

        documento = otro.documento;
        nombre = otro.nombre;
        antiguedadMeses = otro.antiguedadMeses;
        puntuacion = otro.puntuacion;
        cantidadReservas = otro.cantidadReservas;

        if (cantidadReservas > 0) {
            reservas = new string[cantidadReservas];
            for (int i = 0; i < cantidadReservas; ++i)
                reservas[i] = otro.reservas[i];
        } else {
            reservas = nullptr;
        }
    }
    return *this;
}

// Getters
string Huesped::getDocumento() { return documento; }
string Huesped::getNombre() { return nombre; }
int Huesped::getAntiguedad() { return antiguedadMeses; }
float Huesped::getPuntuacion() { return puntuacion; }
int Huesped::getCantidadReservas() { return cantidadReservas; }
string Huesped::getReserva(int i) {
    if (i >= 0 && i < cantidadReservas)
        return reservas[i];
    else
        return "";
}

// Setters
void Huesped::setNombre(string nuevoNombre) { nombre = nuevoNombre; }
void Huesped::setAntiguedad(int meses) { antiguedadMeses = meses; }
void Huesped::setPuntuacion(float nuevaPuntuacion) { puntuacion = nuevaPuntuacion; }
void Huesped::setReservas(string* lista, int cantidad) {
    delete[] reservas;
    cantidadReservas = cantidad;
    reservas = new string[cantidad];
    for (int i = 0; i < cantidad; ++i)
        reservas[i] = lista[i];
}

// Mostrar
void Huesped::mostrarInfo() {
    cout << "Huésped: " << nombre << " (" << documento << ")\n";
    cout << "Antigüedad: " << antiguedadMeses << " meses | Puntuación: " << puntuacion << "\n";
    if (cantidadReservas > 0) {
        cout << "Reservas: ";
        for (int i = 0; i < cantidadReservas; ++i)
            cout << reservas[i] << " ";
        cout << "\n";
    } else {
        cout << "Sin reservas activas\n";
    }
}
