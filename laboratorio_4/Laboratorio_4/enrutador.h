#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <iostream>
#include <map>
#include <string>
using namespace std;

class Enrutador {
private:
    string nombre;  // ID del enrutador
    map<string, int> vecinos;  // vecinos directos y sus costos

public:
    //  Constructor
    Enrutador(string nombre);

    //  Destructor
    ~Enrutador();

    //  Setters
    void establecerNombre(string nuevoNombre);

    //  Getters
    string obtenerNombre() const;

    // Agregar o modificar un vecino
    void agregarVecino(string vecino, int costo);

    // Eliminar un vecino
    void eliminarVecino(string vecino);

    //  Mostrar vecinos
    void mostrarVecinos() const;

    // Obtener el mapa de vecinos
    map<string, int> obtenerVecinos() const;
};

#endif
