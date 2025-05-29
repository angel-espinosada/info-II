#include "reservacion.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

string quitarEspacios(const string& s);

string limpiarNumero(const string& s) {
    string limpio;
    for (char c : s)
        if (isdigit(c)) limpio += c;
    return limpio;
}

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
    cout << "Codigo de reserva: " << codigoReserva << endl;
    cout << "Huesped: " << documentoHuesped << ", Alojamiento: " << codigoAlojamiento << endl;
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
        cout << "No se encontro al anfitrion.\n";
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
        cout << "El anfitrion aun no tiene alojamientos registrados.\n";
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
                cout << "Codigo reserva: " << codRes << endl;
                cout << "Fecha inicio: " << anioIni << "-" << mesIni << "-" << diaIni << " | Noches: " << noches << endl;
                cout << "Alojamiento: " << codAloj << " | Huusped: " << docHuesped << endl;
                cout << "Metodo de pago: " << metodo << " | Fecha de reserva: " << anioRes << "-" << mesRes << "-" << diaRes << endl;
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
    cout << "Ingrese el codigo de la reserva que desea anular: ";
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
        cout << "No se encontro al anfitrion.\n";
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
                cout << "La reserva no pertenece a sus alojamientos. No puede anularla.\n";
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
        cout << "No se encontro la reserva con codigo '" << codigo << "'.\n";
        delete[] reservas;
        delete[] alojamientos;
        return;
    }

    // Confirmar
    char confirmar;
    cout << "¿Esta seguro que desea anular la reserva '" << codigo << "'? (s/n): ";
    cin >> confirmar;
    if (confirmar != 's' && confirmar != 'S') {
        cout << "Operacion cancelada.\n";
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

    cout << " Reserva anulada exitosamente y respaldada.\n";

    delete[] reservas;
    delete[] alojamientos;
}


void Reservacion::actualizarHistorico() {
    string* lineas = nullptr;
    int cantidad = 0;

    if (!leerArchivoTexto("temp_historial.txt", lineas, cantidad)) {
        cout << "No hay reservaciones pendientes de mover al historico.\n";
        return;
    }

    ofstream historico("historico.txt", ios::app); // modo append
    if (!historico.is_open()) {
        cout << "No se pudo abrir el archivo historico.\n";
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

    cout << "Historico actualizado correctamente.\n";
}

//Funcion para busqueda de alojamiento
void Reservacion::buscarAlojamientosDisponibles(const string& documentoSesion)
{
    string municipio, fechaInicio;
    int noches;

    cout << "Ingrese el municipio deseado: ";
    cin.ignore(); // Limpiar buffer
    getline(cin, municipio);

    cout << "Ingrese la fecha de inicio (AAAA-MM-DD): ";
    cin >> fechaInicio;

    cout << "Ingrese la cantidad de noches: ";
    cin >> noches;

    // Leer archivos
    string* alojamientos = nullptr;
    int cantAlojamientos = 0;
    if (!leerArchivoTexto("alojamientos.txt", alojamientos, cantAlojamientos)) {
        cout << "No se pudo leer alojamientos.txt\n";
        return;
    }

    string* anfitriones = nullptr;
    int cantAnfitriones = 0;
    if (!leerArchivoTexto("anfitriones.txt", anfitriones, cantAnfitriones)) {
        cout << "No se pudo leer anfitriones.txt\n";
        delete[] alojamientos; // Liberar alojamientos si falla anfitriones
        return;
    }

    string* reservas = nullptr;
    int cantReservas = 0;
    if (!leerArchivoTexto("reservas.txt", reservas, cantReservas)) {
        cout << "No se pudo leer reservas.txt\n";
        delete[] alojamientos;  // Liberar si falla reservas
        delete[] anfitriones;
        return;
    }

    cout << "\n=== Alojamientos disponibles ===\n";
    int encontrados = 0;

    for (int i = 0; i < cantAlojamientos; ++i) {
        stringstream ss(alojamientos[i]);
        // AQUI: Quitar 'cupoStr' de la declaración si no existe en el TXT
        string cod, nom, dpto, muni, tipo, dir, precioStr, comodidades;

        getline(ss, cod, '|');
        getline(ss, nom, '|');
        getline(ss, dpto, '|');
        getline(ss, muni, '|');
        getline(ss, tipo, '|');
        getline(ss, dir, '|');
        getline(ss, precioStr, '|'); // Ahora lee el precio
        getline(ss, comodidades);    // Ahora lee las comodidades

        cod = quitarEspacios(cod);
        muni = quitarEspacios(muni);

        if (quitarEspacios(muni) != quitarEspacios(municipio)) continue;

        if (!estaDisponible(cod, fechaInicio, noches, reservas, cantReservas)) continue;

        cout << "Codigo: " << cod << " | Nombre: " << nom << endl;
        cout << "Ubicacion: " << muni << ", " << dpto << " | Precio/noche: $" << precioStr << endl;
        // Eliminar o ajustar la línea de "Capacidad" si no existe
        // cout << "Tipo: " << tipo << " | Capacidad: " << cupoStr << " personas" << endl;
        cout << "Tipo: " << tipo << endl; // Puedes quitar "Capacidad" si ya no está en el TXT
        cout << "Comodidades: " << comodidades << endl;
        cout << "---------------------------\n";
        encontrados++;
    }

    if (encontrados == 0) {
        cout << "No se encontraron alojamientos disponibles en el municipio para las fechas indicadas.\n";
    }

    // AQUI: ¡MOVER LOS DELETE[] AL FINAL DE LA FUNCION!
    // delete[] alojamientos;
    // delete[] anfitriones;
    // delete[] reservas;


    if (encontrados == 0) {
        cout << "No se encontraron alojamientos disponibles según los filtros dados.\n";
    } else {
        char confirmar;
        cout << "¿Desea realizar una reserva de uno de estos alojamientos? (s/n): ";
        cin >> confirmar;

        if (confirmar == 's' || confirmar == 'S') {
            string codigoAloj;
            cout << "Ingrese el codigo del alojamiento a reservar: ";
            cin >> codigoAloj;

            string documentoHuesped = documentoSesion;
            // Pedimos método de pago
            string metodoPago;
            cout << "Metodo de pago (TCredito/PSE/Efectivo): ";
            cin >> metodoPago;

            // Obtener fecha de hoy para la reserva
            time_t t = time(nullptr);
            tm* hoy = localtime(&t);
            stringstream fechaReserva;
            fechaReserva << hoy->tm_year + 1900 << "-";
            fechaReserva << (hoy->tm_mon + 1 < 10 ? "0" : "") << hoy->tm_mon + 1 << "-";
            fechaReserva << (hoy->tm_mday < 10 ? "0" : "") << hoy->tm_mday;

            // Calcular fecha final
            string fechaFin = sumarDias(fechaInicio, noches - 1);

            // Valor total (buscar precio del alojamiento)
            double precioNoche = 0;
            cout << "DEBUG >> Buscando precio para codigoAloj: [" << codigoAloj << "]" << endl; // Debug
            for (int i = 0; i < cantAlojamientos; ++i) {
                stringstream ss(alojamientos[i]);
                // AQUI: Quitar 'cupoStr' de la declaración si no existe en el TXT
                string cod, nom, dpto, muni, tipo, dir, precioStr, comodidades;

                getline(ss, cod, '|');
                getline(ss, nom, '|');
                getline(ss, dpto, '|');
                getline(ss, muni, '|');
                getline(ss, tipo, '|');
                getline(ss, dir, '|');
                getline(ss, precioStr, '|'); // ¡Ahora sí lee el precio!
                getline(ss, comodidades);    // Y esto lee las comodidades

                string codAlojamientoActual = quitarEspacios(cod);
                string codigoAlojIngresado = quitarEspacios(codigoAloj);

                cout << "DEBUG >> Comparando en bucle de reserva: [" << codAlojamientoActual << "] con [" << codigoAlojIngresado << "]" << endl; // Debug

                if (codAlojamientoActual == codigoAlojIngresado) {
                    string precioLimpio = quitarEspacios(precioStr); // quitarEspacios también es bueno aquí
                    cout << "DEBUG >> Alojamiento encontrado para reservar. precioStr (limpio): [" << precioLimpio << "]" << endl; // Debug

                    try {
                        precioNoche = stod(precioLimpio);
                        cout << "DEBUG >> Precio por noche convertido exitosamente: $" << precioNoche << endl; // Debug
                    } catch (const std::invalid_argument& ia) { // Captura específica de errores
                        cerr << "❌ ERROR: Argumento invalido para stod() - '" << precioLimpio << "'. " << ia.what() << endl;
                        precioNoche = 0;
                    } catch (const std::out_of_range& oor) { // Captura específica de errores
                        cerr << "❌ ERROR: Fuera de rango para stod() - '" << precioLimpio << "'. " << oor.what() << endl;
                        precioNoche = 0;
                    } catch (...) { // Captura cualquier otra excepción
                        cout << "❌ Error al convertir a double (desconocido): [" << precioLimpio << "]\n";
                        precioNoche = 0;
                    }
                    break;
                }
            }


            cout << "DEBUG >> Precio final por noche: " << precioNoche << endl; // Nuevo debug
            cout << "DEBUG >> Noches ingresadas: " << noches << endl;          // Nuevo debug
            double total = precioNoche * noches;
            cout << "DEBUG >> Total final calculado: $" << total << endl; // Debug más descriptivo

            // Generar código de reserva (puedes hacerlo mejor)
            string codigoReserva = "R";
            codigoReserva += to_string(rand() % 900 + 100); // RXXX

            // Formato de línea:
            // codigoReserva-AñoInicio-MesInicio-DiaInicio-Noches-CodigoAloj-DocumentoHuesped-MetodoPago-AñoReserva-MesReserva-DiaReserva-Total
            ofstream out("reservas.txt", ios::app);
            if (out.is_open()) {
                out << codigoReserva << "-"
                    << fechaInicio.substr(0,4) << "-"
                    << fechaInicio.substr(5,2) << "-"
                    << fechaInicio.substr(8,2) << "-"
                    << noches << "-"
                    << codigoAloj << "-"
                    << documentoHuesped << "-"
                    << metodoPago << "-"
                    << fechaReserva.str().substr(0,4) << "-"
                    << fechaReserva.str().substr(5,2) << "-"
                    << fechaReserva.str().substr(8,2) << "-"
                    << int(total) << endl;

                cout << "Reserva creada con Exito.\n";
                cout << "Codigo: " << codigoReserva << " | Total pagado: $" << int(total) << endl;
                cout << "Desde: " << fechaInicio << " hasta " << fechaFin << endl;
            } else {
                cout << "Error al guardar la reserva.\n";
            }
        }
    }

    // AQUI: LIBERAR LA MEMORIA AL FINAL
    delete[] alojamientos;
    delete[] anfitriones;
    delete[] reservas;

}

bool estaDisponible(const string& codAlojamiento, const string& fechaInicio, int noches, string* reservas, int cantidadReservas) {
    string* lineas = nullptr;
    int cantidad = 0;
    if (!leerArchivoTexto("reservas.txt", lineas, cantidad)) return false;

    string fechaFin = sumarDias(fechaInicio, noches - 1);

    for (int i = 0; i < cantidad; ++i) {
        stringstream ss(lineas[i]);
        string codRes, anio, mes, dia, nochesRes, codAloj;
        getline(ss, codRes, '-');
        getline(ss, anio, '-');
        getline(ss, mes, '-');
        getline(ss, dia, '-');
        getline(ss, nochesRes, '-');
        getline(ss, codAloj, '-');

        codAloj = quitarEspacios(codAloj);
        if (codAloj != codAlojamiento) continue;

        string fechaIniExistente = anio + "-" + mes + "-" + dia;
        string fechaFinExistente = sumarDias(fechaIniExistente, stoi(nochesRes) - 1);

        if (fechasSeSolapan(fechaInicio, fechaFin, fechaIniExistente, fechaFinExistente)) {
            delete[] lineas;
            return false;
        }
    }

    delete[] lineas;
    return true;
}

tm fechaA_tm(const string& fecha) {
    tm tiempo = {};
    stringstream ss(fecha);
    string anio, mes, dia;
    getline(ss, anio, '-');
    getline(ss, mes, '-');
    getline(ss, dia, '-');

    tiempo.tm_year = stoi(anio) - 1900;
    tiempo.tm_mon = stoi(mes) - 1;
    tiempo.tm_mday = stoi(dia);

    mktime(&tiempo);
    return tiempo;
}


string tmAFecha(const tm& tiempo) {
    stringstream ss;
    ss << (tiempo.tm_year + 1900) << "-";
    if (tiempo.tm_mon + 1 < 10) ss << "0";
    ss << (tiempo.tm_mon + 1) << "-";
    if (tiempo.tm_mday < 10) ss << "0";
    ss << tiempo.tm_mday;
    return ss.str();
}


string sumarDias(const string& fechaInicio, int dias) {
    tm fecha = fechaA_tm(fechaInicio);
    fecha.tm_mday += dias;
    mktime(&fecha);
    return tmAFecha(fecha);
}

bool fechasSeSolapan(const string& inicio1, const string& fin1, const string& inicio2, const string& fin2) {
    tm ini1 = fechaA_tm(inicio1);
    tm fin1_ = fechaA_tm(fin1);
    tm ini2 = fechaA_tm(inicio2);
    tm fin2_ = fechaA_tm(fin2);

    time_t t_ini1 = mktime(&ini1);
    time_t t_fin1 = mktime(&fin1_);
    time_t t_ini2 = mktime(&ini2);
    time_t t_fin2 = mktime(&fin2_);

    return !(t_fin1 < t_ini2 || t_fin2 < t_ini1);
}

void Reservacion::verReservasHuesped(const string& documentoHuesped) {
    string* lineas = nullptr;
    int cantidad = 0;

    if (!leerArchivoTexto("reservas.txt", lineas, cantidad)) {
        cout << "No se pudo leer el archivo de reservas.\n";
        return;
    }

    bool encontrado = false;
    cout << "\n=== Reservaciones Activas ===\n";
    for (int i = 0; i < cantidad; ++i) {
        stringstream ss(lineas[i]);
        string codRes, anioIni, mesIni, diaIni;
        string noches, codAloj, docHuesped, metodo;
        string anioRes, mesRes, diaRes, total;

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
        getline(ss, total);

        if (quitarEspacios(docHuesped) == quitarEspacios(documentoHuesped)) {
            encontrado = true;
            cout << "\nCodigo reserva: " << codRes << endl;
            cout << "Inicio: " << anioIni << "-" << mesIni << "-" << diaIni << " | Noches: " << noches << endl;
            cout << "Alojamiento: " << codAloj << " | Metodo de pago: " << metodo << endl;
            cout << "Reservada el: " << anioRes << "-" << mesRes << "-" << diaRes << " | Total: $" << total << endl;
            cout << "-----------------------------------";
        }
    }

    if (!encontrado) {
        cout << "No tienes reservas activas.\n";
    }

    delete[] lineas;
}


void Reservacion::anularReservacionHuesped(const string& documentoHuesped) {
    string codigo;
    cout << "Ingrese el codigo de la reserva que desea anular: ";
    cin >> codigo;

    string* reservas = nullptr;
    int totalReservas = 0;
    if (!leerArchivoTexto("reservas.txt", reservas, totalReservas)) {
        cout << "No se pudo leer reservas.txt\n";
        return;
    }

    int indiceEliminar = -1;
    for (int i = 0; i < totalReservas; ++i) {
        stringstream ss(reservas[i]);
        string codRes, anio, mes, dia, noches, codAloj, docHuesped;

        getline(ss, codRes, '-');
        getline(ss, anio, '-');
        getline(ss, mes, '-');
        getline(ss, dia, '-');
        getline(ss, noches, '-');
        getline(ss, codAloj, '-');
        getline(ss, docHuesped, '-');

        if (quitarEspacios(codRes) == quitarEspacios(codigo) &&
            quitarEspacios(docHuesped) == quitarEspacios(documentoHuesped)) {
            indiceEliminar = i;
            break;
        }
    }

    if (indiceEliminar == -1) {
        cout << "No se encontro una reserva activa con ese codigo para usted.\n";
        delete[] reservas;
        return;
    }

    // Confirmar
    char confirmar;
    cout << "¿Esta seguro que desea anular la reserva '" << codigo << "'? (s/n): ";
    cin >> confirmar;
    if (confirmar != 's' && confirmar != 'S') {
        cout << "Operacion cancelada.\n";
        delete[] reservas;
        return;
    }

    // Guardar respaldo
    ofstream tempHist("temp_historial.txt", ios::app);
    if (tempHist.is_open()) {
        tempHist << reservas[indiceEliminar] << endl;
        tempHist.close();
    }

    // Reescribir archivo excluyendo esa línea
    ofstream out("reservas.txt");
    for (int i = 0; i < totalReservas; ++i) {
        if (i != indiceEliminar) {
            out << reservas[i] << endl;
        }
    }

    cout << "Reserva anulada exitosamente y respaldada temporalmente.\n";
    delete[] reservas;
}

