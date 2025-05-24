#include <iostream>
#include "anfitrion.h"
#include <fstream>
#include <sstream>


using namespace std;

bool leerAnfitrionesDesdeArchivo(Anfitrion* &lista, int &cantidad);

int main()
{

    //Anfitrion a1("123456789", "Laura Restrepo", 15, 4.8);
   // a1.mostrarInfo();



    Anfitrion* anfitriones = nullptr;
    int cantidad = 0;

    if (leerAnfitrionesDesdeArchivo(anfitriones, cantidad)) {
        for (int i = 0; i < cantidad; ++i) {
            cout << "Anfitrión: " << anfitriones[i].getNombre() << " (" << anfitriones[i].getNumeroDocumento() << ")\n";
            cout << "  Antigüedad: " << anfitriones[i].getAntiguedad() << " meses | Puntuación: " << anfitriones[i].getPuntuacion() << "\n";

            if (anfitriones[i].getCantidadAlojamientos() > 0) {
                cout << "  Alojamientos: ";
                for (int j = 0; j < anfitriones[i].getCantidadAlojamientos(); ++j)
                    cout << anfitriones[i].getAlojamiento(j) << " ";
                cout << "\n";
            } else {
                cout << "  Sin alojamientos.\n";
            }
        }

        // liberar memoria


        delete[] anfitriones;
    }

    return 0;





}

bool leerAnfitrionesDesdeArchivo(Anfitrion* &lista, int &cantidad) {
    ifstream in("anfitriones.txt");
    if (!in.is_open()) {
        cout << "No se encontró el archivo anfitriones.txt\n";
        return false;
    }

    string linea;
    cantidad = 0;
    int capacidad = 10;
    lista = new Anfitrion[capacidad];

    while (getline(in, linea)) {
        stringstream ss(linea);
        string doc, nombre, antiguedadStr, puntuacionStr, alojamientosStr;

        getline(ss, doc, '-');
        getline(ss, nombre, '-');
        getline(ss, antiguedadStr, '-');
        getline(ss, puntuacionStr, '-');
        getline(ss, alojamientosStr);  // puede estar vacío

        if (cantidad >= capacidad) {
            capacidad *= 2;
            Anfitrion* nuevaLista = new Anfitrion[capacidad];
            for (int i = 0; i < cantidad; ++i)
                nuevaLista[i] = lista[i];
            delete[] lista;
            lista = nuevaLista;
        }

        Anfitrion a(doc, nombre, stoi(antiguedadStr), stof(puntuacionStr));

        if (!alojamientosStr.empty()) {
            stringstream alojStream(alojamientosStr);
            string cod;
            int count = 0;
            string temp[10];

            while (getline(alojStream, cod, ',')) {
                temp[count++] = cod;
            }

            a.setAlojamientos(temp, count);
        } else {
            a.setAlojamientos(nullptr, 0);
        }

        lista[cantidad++] = a;
    }

    in.close();
    return true;
}
