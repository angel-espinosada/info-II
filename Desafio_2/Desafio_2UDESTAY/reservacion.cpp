#include "reservacion.h"
#include <iostream>

using namespace std;

// Declaración de función externa
extern bool leerArchivoTexto(const string& nombreArchivo, string* &lineas, int &cantidadLineas);

// Constructor vacío
Reservacion::Reservacion() {}

// Constructor con parámetros
Reservacion::Reservacion(string codRes, string docH, string codAloj, string inicio, string fin, string est)
    : codigoReserva(codRes), documentoHuesped(docH), codigoAlojamiento(codAloj),
    fechaInicio(inicio), fechaFin(fin), estado(est) {}

// Getters
string Reservacion::getCodigoReserva() const { return codigoReserva; }
string Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
string Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
string Reservacion::getFechaInicio() const { return fechaInicio; }
string Reservacion::getFechaFin() const { return fechaFin; }
string Reservacion::getEstado() const { return estado; }

// Setter
void Reservacion::setEstado(const string& nuevoEstado) {
    estado = nuevoEstado;
}

// Mostrar info
void Reservacion::mostrar() {
    cout << "Código de reserva: " << codigoReserva << endl;
    cout << "Huésped: " << documentoHuesped << ", Alojamiento: " << codigoAlojamiento << endl;
    cout << "Desde: " << fechaInicio << " hasta " << fechaFin << ", Estado: " << estado << endl;
}

// Convertir a línea de texto para guardar
string Reservacion::toLineaTexto() {
    return codigoReserva + "-" + documentoHuesped + "-" + codigoAlojamiento + "-" +
           fechaInicio + "-" + fechaFin + "-" + estado;
}

// Mostrar reservaciones de un anfitrión
void Reservacion::verReservacionesAnfitrion(const string& documentoAnfitrion) {
    string* lineas = nullptr;
    int cantidad = 0;

    // 1. Leer anfitriones.txt
    if (!leerArchivoTexto("anfitriones.txt", lineas, cantidad)) {
        cout << "No se pudo leer anfitriones.txt\n";
        return;
    }

    string* codigosAlojamiento = new string[20];
    int totalAlojamientos = 0;

    for (int i = 0; i < cantidad; ++i) {
        if (lineas[i].substr(0, documentoAnfitrion.length()) == documentoAnfitrion) {
            int pos = 0, guion = 0, count = 0;
            while (count < 4 && (guion = lineas[i].find('-', pos)) != -1) {
                pos = guion + 1;
                count++;
            }

            string alojamientosStr = lineas[i].substr(pos);
            int ini = 0, coma;
            while ((coma = alojamientosStr.find(',', ini)) != -1) {
                codigosAlojamiento[totalAlojamientos++] = alojamientosStr.substr(ini, coma - ini);
                ini = coma + 1;
            }
            if (ini < alojamientosStr.length()) {
                codigosAlojamiento[totalAlojamientos++] = alojamientosStr.substr(ini);
            }
            break;
        }
    }

    delete[] lineas;

    if (totalAlojamientos == 0) {
        cout << "No se encontraron alojamientos para el anfitrión.\n";
        delete[] codigosAlojamiento;
        return;
    }

    // 2. Leer reservas.txt
    lineas = nullptr;
    cantidad = 0;
    if (!leerArchivoTexto("reservas.txt", lineas, cantidad)) {
        cout << "No se pudo leer reservas.txt\n";
        delete[] codigosAlojamiento;
        return;
    }

    cout << "\n=== Reservaciones encontradas ===\n";
    bool encontro = false;

    for (int i = 0; i < cantidad; ++i) {
        int pos = 0;
        string campos[5];
        for (int j = 0; j < 5; ++j) {
            int guion = lineas[i].find('-', pos);
            if (guion == -1) {
                campos[j] = lineas[i].substr(pos);  // resto de línea
                break;
            }
            campos[j] = lineas[i].substr(pos, guion - pos);
            pos = guion + 1;
        }

        string codAloj = campos[3];
        for (int j = 0; j < totalAlojamientos; ++j) {
            if (codAloj == codigosAlojamiento[j]) {
                cout << "→ " << lineas[i] << endl;
                encontro = true;
                break;
            }
        }
    }

    if (!encontro) {
        cout << "No hay reservaciones activas para sus alojamientos.\n";
    }

    delete[] lineas;
    delete[] codigosAlojamiento;
}
