#include "reservacion.h"
#include <iostream>
#include <sstream>
using namespace std;
string quitarEspacios(const string& s) {
    string limpio = "";
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != ' ') limpio += s[i];
    }
    return limpio;
}
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
    //cout << "\n[DEBUG] Entrando a verReservacionesAnfitrion con doc: " << documentoAnfitrion << endl;

    string* lineas = nullptr;
    int cantidad = 0;

    // 1. Leer anfitriones.txt
    if (!leerArchivoTexto("anfitriones.txt", lineas, cantidad)) {
        cout << "Error al leer anfitriones.txt\n";
        return;
    }

    // 2. Buscar la línea del anfitrión
    string lineaAnfitrion = "";
    for (int i = 0; i < cantidad; ++i) {
        if (lineas[i].substr(0, documentoAnfitrion.length()) == documentoAnfitrion) {
            lineaAnfitrion = lineas[i];
            break;
        }
    }
    delete[] lineas;

    if (lineaAnfitrion == "") {
        cout << "No se encontró al anfitrión.\n";
        return;
    }

    //cout << "[DEBUG] Línea del anfitrión encontrada: " << lineaAnfitrion << endl;

    // 3. Extraer los códigos de alojamiento
    int conteoComas = 0;
    for (int i = 0; i < lineaAnfitrion.length(); ++i)
        if (lineaAnfitrion[i] == ',') conteoComas++;

    int cantidadAlojamientos = conteoComas + 1;
    string* alojamientos = new string[cantidadAlojamientos];

    // Saltar 4 campos
    int pos = 0;
    for (int i = 0; i < 4; ++i) {
        while (pos < lineaAnfitrion.length() && lineaAnfitrion[pos] != '-') pos++;
        pos++;
    }

    int inicio = pos, idx = 0;
    for (int i = pos; i <= lineaAnfitrion.length(); ++i) {
        if (lineaAnfitrion[i] == ',' || lineaAnfitrion[i] == '\0') {
            alojamientos[idx++] = quitarEspacios(lineaAnfitrion.substr(inicio, i - inicio));
            inicio = i + 1;
        }
    }

    //cout << "[DEBUG] Códigos de alojamiento encontrados:\n";
    for (int i = 0; i < cantidadAlojamientos; ++i)
        cout << "   - " << alojamientos[i] << endl;

    // 4. Leer reservas.txt
    lineas = nullptr;
    cantidad = 0;

    if (!leerArchivoTexto("reservas.txt", lineas, cantidad)) {
        cout << "No se pudo leer reservas.txt\n";
        delete[] alojamientos;
        return;
    }

    bool encontro = false;
    cout << "\n=== Reservaciones encontradas ===\n";

    for (int i = 0; i < cantidad; ++i) {
        //cout << "[DEBUG] Analizando línea de reserva: " << lineas[i] << endl;

        // Extraer código de alojamiento usando stringstream
        // Extraer código de alojamiento correctamente
        stringstream ss(lineas[i]);
        string codRes, anio, mes, dia, noches, codAloj;
        getline(ss, codRes, '-');
        getline(ss, anio, '-');
        getline(ss, mes, '-');
        getline(ss, dia, '-');
        getline(ss, noches, '-');
        getline(ss, codAloj, '-');

        // Si necesitás la fecha completa:
        //string fechaInicio = anio + "-" + mes + "-" + dia;

        codAloj = quitarEspacios(codAloj);
        //cout << "[DEBUG] Código alojamiento de reserva: '" << codAloj << "'\n";


        // Comparar con los códigos del anfitrión
        for (int j = 0; j < cantidadAlojamientos; ++j) {
            //cout << "[DEBUG] Comparando con: '" << alojamientos[j] << "'\n";
            if (alojamientos[j] == codAloj) {
                cout << "Item " << lineas[i] << endl;
                encontro = true;
                break;
            }
        }
    }

    if (!encontro) {
        cout << "No hay reservaciones activas para sus alojamientos.\n";
    }

    delete[] alojamientos;
    delete[] lineas;
}
