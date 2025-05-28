#include <QCoreApplication>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ifstream archivoM1("M1.txt");
    if (!archivoM1.is_open()) {
        cerr << "Error: No se pudo abrir M1.txt" << endl;
        return -1;
    }

    // Leer la semilla
    int semilla = 0;
    archivoM1 >> semilla;
    cout << "Semilla leída: " << semilla << endl;

    // Contar cuántos valores RGB hay
    int valor = 0;
    int contador = 0;

    while (archivoM1 >> valor) {
        contador++;
    }

    archivoM1.close();

    // Recordemos: cada píxel tiene 3 valores (R, G, B)
    if (contador % 3 != 0) {
        cerr << "Error: El archivo no tiene tripletas RGB completas." << endl;
        return -1;
    }

    int cantidadPixeles = contador / 3;
    cout << "Cantidad de píxeles en M1.txt: " << cantidadPixeles << endl;

    return 0;
}
