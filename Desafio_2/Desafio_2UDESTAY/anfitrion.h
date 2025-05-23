
#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>
using namespace std;

class Anfitrion {
private:
    string numeroDocumento;
    string nombre;
    int antiguedadMeses;
    float puntuacion;

public:
    // Constructor por defecto
    Anfitrion();

    // Constructor con parámetros
    Anfitrion(string doc, string nombre, int antiguedad, float punt);

    // Destructor
    ~Anfitrion();

    // Getters
    string getNumeroDocumento();
    string getNombre();
    int getAntiguedad();
    float getPuntuacion();

    // Setters
    void setNombre(string nuevoNombre);
    void setAntiguedad(int meses);
    void setPuntuacion(float nuevaPuntuacion);

    // Función extra: mostrar información (útil para debug o pruebas)
    void mostrarInfo();
};

#endif // ANFITRION_H
