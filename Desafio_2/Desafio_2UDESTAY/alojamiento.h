#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
using namespace std;

class Alojamiento {
private:
    string codigo;
    string municipio;
    string direccion;
    int capacidad;
    float costoPorNoche;
    string documentoAnfitrion;

public:
    // Constructores
    Alojamiento();
    Alojamiento(string cod, string mun, string dir, int cap, float costo, string docAnfitrion);

    // Getters
    string getCodigo() const;
    string getMunicipio() const;
    string getDireccion() const;
    int getCapacidad() const;
    float getCostoPorNoche() const;
    string getDocumentoAnfitrion() const;

    // Setters
    void setCostoPorNoche(float nuevoCosto);

    // Utilidad
    void mostrar() const;
    string toLineaTexto() const;
};

#endif // ALOJAMIENTO_H
