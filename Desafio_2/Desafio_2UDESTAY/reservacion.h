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

    //void anularReservacion();
    void actualizarHistorico();
    void anularReservacion(const string& documentoAnfitrion);

    void buscarAlojamientosDisponibles();
    void verReservasHuesped(const string& documentoHuesped);





};

tm fechaA_tm(const string& fecha);
string tmAFecha(const tm& tiempo);
string sumarDias(const string& fechaInicio, int dias);
bool fechasSeSolapan(const string& inicio1, const string& fin1, const string& inicio2, const string& fin2);
bool estaDisponible(const string& codAlojamiento, const string& fechaInicio, int noches, string* reservas, int cantidadReservas);


#endif // RESERVACION_H
