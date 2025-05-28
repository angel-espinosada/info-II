#include "reservacion.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

string quitarEspacios(const string& s);

// Variable global para usar en el filtro
static string codigoAEliminar = "";

// Función auxiliar para filtrar la línea a eliminar
static bool filtroReservas(const string& linea) {
    return quitarEspacios(linea.substr(0, codigoAEliminar.length())) != quitarEspacios(codigoAEliminar);
}

string quitarEspacios(const string& s) {
    string limpio = "";
    for (int i = 0; i < s.length(); ++i)
        if (s[i] != ' ') limpio += s[i];
    return limpio;
}

// Declaración de función externa
extern bool leerArchivoTexto(const string& nombreArchivo, string* &lineas, int &cantidadLineas);
extern bool reescribirArchivoFiltrado(const std::string& nombreArchivo, bool (*filtro)(const std::string&));

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

    // 3. Extraer los códigos de alojamiento
    int conteoComas = 0;
    for (int i = 0; i < lineaAnfitrion.length(); ++i)
        if (lineaAnfitrion[i] == ',') conteoComas++;

    int cantidadAlojamientos = conteoComas + 1;
    string* alojamientos = new string[cantidadAlojamientos];

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

    // 4. Leer reservas.txt
    lineas = nullptr;
    cantidad = 0;
    if (cantidadAlojamientos == 0 || alojamientos[0] == "") {
        cout << "El anfitrión aún no tiene alojamientos registrados.\n";
        delete[] alojamientos;
        return;
    }
    if (!leerArchivoTexto("reservas.txt", lineas, cantidad)) {
        cout << "No se pudo leer reservas.txt\n";
        delete[] alojamientos;
        return;
    }

    bool encontro = false;
    cout << "\n=== Reservaciones encontradas ===\n";

    for (int i = 0; i < cantidad; ++i) {
        stringstream ss(lineas[i]);

        string codRes, anioIni, mesIni, diaIni;
        string noches, codAloj, docHuesped, metodo;
        string anioRes, mesRes, diaRes;
        string valor, nota;

        getline(ss, codRes, '-');
        getline(ss, anioIni, '-');
        getline(ss, mesIni, '-');
        getline(ss, diaIni, '-');
        getline(ss, noches, '-');
        getline(ss, codAloj, '-');
        getline(ss, docHuesped, '-');
        getline(ss, metodo, '-');
        getline(ss, anioRes, '-');
        getline(ss, mesRes, '-');
        getline(ss, diaRes, '-');
        getline(ss, valor, '-');  // Este es el valor
        getline(ss, nota);        // Nota (opcional)

        codAloj = quitarEspacios(codAloj);

        for (int j = 0; j < cantidadAlojamientos; ++j) {
            if (alojamientos[j] == codAloj) {
                encontro = true;
                cout << "------------------------------\n";
                cout << "Código reserva: " << codRes << endl;
                cout << "Fecha inicio: " << anioIni << "-" << mesIni << "-" << diaIni << " | Noches: " << noches << endl;
                cout << "Alojamiento: " << codAloj << " | Huésped: " << docHuesped << endl;
                cout << "Método de pago: " << metodo << " | Fecha de reserva: " << anioRes << "-" << mesRes << "-" << diaRes << endl;
                cout << "Valor pagado: $" << valor << endl;
                if (!nota.empty()) cout << "Nota: " << nota << endl;
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

void Reservacion::anularReservacion(const string& documentoAnfitrion) {
    string codigo;
    cout << "Ingrese el código de la reserva que desea anular: ";
    cin >> codigo;

    // Obtener alojamientos del anfitrión
    string* lineas = nullptr;
    int cantidad = 0;
    if (!leerArchivoTexto("anfitriones.txt", lineas, cantidad)) {
        cout << "No se pudo leer anfitriones.txt\n";
        return;
    }

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

    // Extraer alojamientos
    string* alojamientos = new string[10];
    int cantidadAlojamientos = 0;

    int pos = 0;
    for (int i = 0; i < 4; ++i) {
        while (pos < lineaAnfitrion.length() && lineaAnfitrion[pos] != '-') pos++;
        pos++;
    }

    int inicio = pos;
    for (int i = pos; i <= lineaAnfitrion.length(); ++i) {
        if (lineaAnfitrion[i] == ',' || lineaAnfitrion[i] == '\0') {
            alojamientos[cantidadAlojamientos++] = quitarEspacios(lineaAnfitrion.substr(inicio, i - inicio));
            inicio = i + 1;
        }
    }

    // Leer reservas.txt
    string* reservas = nullptr;
    int totalReservas = 0;
    if (!leerArchivoTexto("reservas.txt", reservas, totalReservas)) {
        cout << "No se pudo leer reservas.txt\n";
        delete[] alojamientos;
        return;
    }

    // Buscar reserva y validar que sea del anfitrión
    bool encontrada = false;
    int indiceEliminar = -1;
    string codigoAlojamiento = "";

    for (int i = 0; i < totalReservas; ++i) {
        if (quitarEspacios(reservas[i].substr(0, codigo.length())) == quitarEspacios(codigo)) {
            // Extraer código alojamiento
            stringstream ss(reservas[i]);
            string campo;
            for (int j = 0; j < 5; ++j) getline(ss, campo, '-');  // Quinto campo
            codigoAlojamiento = quitarEspacios(campo);

            // Validar que pertenezca al anfitrión
            bool pertenece = false;
            for (int j = 0; j < cantidadAlojamientos; ++j) {
                if (alojamientos[j] == codigoAlojamiento) {
                    pertenece = true;
                    break;
                }
            }

            if (!pertenece) {
                cout << "✖ La reserva no pertenece a sus alojamientos. No puede anularla.\n";
                delete[] reservas;
                delete[] alojamientos;
                return;
            }

            // Validación aprobada
            encontrada = true;
            indiceEliminar = i;
            break;
        }
    }

    if (!encontrada) {
        cout << "✖ No se encontró la reserva con código '" << codigo << "'.\n";
        delete[] reservas;
        delete[] alojamientos;
        return;
    }

    // Confirmar
    char confirmar;
    cout << "¿Está seguro que desea anular la reserva '" << codigo << "'? (s/n): ";
    cin >> confirmar;
    if (confirmar != 's' && confirmar != 'S') {
        cout << "✱ Operación cancelada.\n";
        delete[] reservas;
        delete[] alojamientos;
        return;
    }

    // Guardar respaldo
    ofstream tempHist("temp_historial.txt", ios::app);
    if (tempHist.is_open()) {
        tempHist << reservas[indiceEliminar] << endl;
        tempHist.close();
    }

    // Reescribir reservas.txt
    ofstream out("reservas.txt");
    for (int i = 0; i < totalReservas; ++i) {
        if (i != indiceEliminar)
            out << reservas[i] << endl;
    }

    cout << "✔ Reserva anulada exitosamente y respaldada.\n";

    delete[] reservas;
    delete[] alojamientos;
}


void Reservacion::actualizarHistorico() {
    string* lineas = nullptr;
    int cantidad = 0;

    if (!leerArchivoTexto("temp_historial.txt", lineas, cantidad)) {
        cout << "⚠ No hay reservaciones pendientes de mover al histórico.\n";
        return;
    }

    ofstream historico("historico.txt", ios::app); // modo append
    if (!historico.is_open()) {
        cout << "✖ No se pudo abrir el archivo histórico.\n";
        delete[] lineas;
        return;
    }

    for (int i = 0; i < cantidad; ++i) {
        historico << lineas[i] << endl;
    }
    historico.close();
    delete[] lineas;

    // Limpiar temp_historico.txt
    ofstream limpiar("temp_historial.txt", ios::trunc);
    limpiar.close();

    cout << "✔ Histórico actualizado correctamente.\n";
}
