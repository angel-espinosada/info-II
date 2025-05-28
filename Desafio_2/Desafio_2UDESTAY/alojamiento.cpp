#include "alojamiento.h"
#include <iostream>

Alojamiento::Alojamiento() {}

Alojamiento::Alojamiento(string cod, string mun, string dir, int cap, float costo, string docAnfitrion)
    : codigo(cod), municipio(mun), direccion(dir), capacidad(cap), costoPorNoche(costo), documentoAnfitrion(docAnfitrion) {}

string Alojamiento::getCodigo() const { return codigo; }
string Alojamiento::getMunicipio() const { return municipio; }
string Alojamiento::getDireccion() const { return direccion; }
int Alojamiento::getCapacidad() const { return capacidad; }
float Alojamiento::getCostoPorNoche() const { return costoPorNoche; }
string Alojamiento::getDocumentoAnfitrion() const { return documentoAnfitrion; }

void Alojamiento::setCostoPorNoche(float nuevoCosto) {
    costoPorNoche = nuevoCosto;
}

void Alojamiento::mostrar() const {
    cout << "Código: " << codigo << ", Municipio: " << municipio << ", Dirección: " << direccion << endl;
    cout << "Capacidad: " << capacidad << ", Costo por noche: $" << costoPorNoche << endl;
    cout << "Anfitrión: " << documentoAnfitrion << endl;
}

string Alojamiento::toLineaTexto() const {
    return codigo + "-" + municipio + "-" + direccion + "-" +
           to_string(capacidad) + "-" + to_string(costoPorNoche) + "-" + documentoAnfitrion;
}
