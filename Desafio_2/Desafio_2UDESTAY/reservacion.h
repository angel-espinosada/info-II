#ifndef RESERVACION_H
#define RESERVACION_H

#include <string>
using namespace std;

class Reservacion {
private:
    string codigoReserva;
    string documentoHuesped;
    string codigoAlojamiento;
    string fechaInicio;
    string fechaFin;
    string estado;

public:
    // Constructores
    Reservacion();
    Reservacion(string codRes, string docH, string codAloj, string inicio, string fin, string est = "activa");

    // Getters
    string getCodigoReserva() const;
    string getDocumentoHuesped() const;
    string getCodigoAlojamiento() const;
    string getFechaInicio() const;
    string getFechaFin() const;
    string getEstado() const;

    // Setters
    void setEstado(const string& nuevoEstado);

    // Utilidad
    void mostrar();
    string toLineaTexto();
    void verReservacionesAnfitrion(const string& documentoAnfitrion);

};

#endif // RESERVACION_H
