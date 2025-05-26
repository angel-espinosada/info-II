#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <map>
#include <string>
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
};

#endif // RED_H
