#include "Red.h"
#include <iostream>

using namespace std;

Red::Red() {}

void Red::agregarEnrutador(const string& nombre){
    enrutadores[nombre] = Enrutador(nombre);  // ← Pasa el nombre al constructor
}


// Elimina un enrutador y lo quita de los vecinos de los demás
void Red::eliminarEnrutador(const string& nombre) {
    enrutadores.erase(nombre);
    for (auto& par : enrutadores) {
        par.second.eliminarVecino(nombre);
    }
}

// Conecta dos enrutadores (origen y destino) con un costo
void Red::conectarEnrutadores(const string& origen, const string& destino, int costo) {
    enrutadores[origen].agregarVecino(destino, costo);
}

// Muestra todos los enrutadores y sus vecinos
void Red::mostrarRed() const {
    for (const auto& par : enrutadores) {
        par.second.mostrarVecinos();
        cout << endl;
    }
}
