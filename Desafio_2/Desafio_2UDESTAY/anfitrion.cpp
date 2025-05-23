#include "anfitrion.h"
#include <iostream>

Anfitrion::Anfitrion() {}

Anfitrion::Anfitrion(string doc, string nombre, int antiguedad, float punt)
    : numeroDocumento(doc), nombre(nombre), antiguedadMeses(antiguedad), puntuacion(punt) {}

Anfitrion::~Anfitrion() {}

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

void Anfitrion::setNombre(std::string nuevoNombre) {
    nombre = nuevoNombre;
}

void Anfitrion::setAntiguedad(int meses) {
    antiguedadMeses = meses;
}

void Anfitrion::setPuntuacion(float nuevaPuntuacion) {
    puntuacion = nuevaPuntuacion;
}

void Anfitrion::mostrarInfo() {
    cout << "Anfitrion: " << nombre << " (" << numeroDocumento << ")" << std::endl;
    cout << "Antiguedad: " << antiguedadMeses << " meses | Puntuacion: " << puntuacion << std::endl;
}
