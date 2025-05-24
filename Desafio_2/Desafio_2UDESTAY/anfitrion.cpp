#include "anfitrion.h"
#include <iostream>

Anfitrion::Anfitrion() {
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



Anfitrion::~Anfitrion() {
    delete[] alojamientos;
}

// Getters
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
    else
        return "";
}

// Setters
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
    // Eliminar anteriores si hay
    delete[] alojamientos;
    cantidadAlojamientos = cantidad;
    alojamientos = new string[cantidad];
    for (int i = 0; i < cantidad; ++i)
        alojamientos[i] = lista[i];
}

void Anfitrion::mostrarInfo() {
    std::cout << "Anfitrión: " << nombre << " (" << numeroDocumento << ")\n";
    std::cout << "Antigüedad: " << antiguedadMeses << " meses | Puntuación: " << puntuacion << "\n";
    if (cantidadAlojamientos > 0) {
        std::cout << "Alojamientos: ";
        for (int i = 0; i < cantidadAlojamientos; ++i)
            std::cout << alojamientos[i] << " ";
        std::cout << "\n";
    } else {
        std::cout << "Sin alojamientos\n";
    }
}
