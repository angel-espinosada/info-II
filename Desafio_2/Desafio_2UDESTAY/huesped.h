#ifndef HUESPED_H
#define HUESPED_H

#include <string>
using namespace std;

class Huesped {
private:
    string documento;
    string nombre;
    int antiguedadMeses;
    float puntuacion;
    string* reservas;
    int cantidadReservas;

public:
    Huesped();
    Huesped(string doc, string nom, int ant, float punt);
    Huesped(const Huesped& otro);
    ~Huesped();
    Huesped& operator=(const Huesped& otro);

    // Getters
    string getDocumento();
    string getNombre();
    int getAntiguedad();
    float getPuntuacion();
    int getCantidadReservas();
    string getReserva(int i);

    // Setters
    void setNombre(string nuevoNombre);
    void setAntiguedad(int meses);
    void setPuntuacion(float nuevaPuntuacion);
    void setReservas(string* lista, int cantidad);

    void mostrarInfo();
};

#endif
