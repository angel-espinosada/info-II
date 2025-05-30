#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <map>
#include <string>
#include <set>

using namespace std;
class Red {
private:
    map<string, Enrutador> enrutadores;

public:
    // Constructor
    Red();

    // Métodos principales
    void agregarEnrutador(const string& nombre);
    void eliminarEnrutador(const string& nombre);
    void conectarEnrutadores(const string& origen, const string& destino, int costo);
    void mostrarRed() const;

    void encontrarRutaMinima(const string& origen, const string& destino) const;
    void mostrarEnrutadores() const;
    void rutaMinimaConEstadisticas(const string& origen, const string& destino);
    void generarRedAleatoria(int cantidad);
    void guardarEnArchivo(const string& nombreArchivo) const;
    void cargarDesdeArchivo(const string& nombreArchivo);


};

#endif // RED_H
