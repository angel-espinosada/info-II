#include <iostream>
using namespace std;

int main() {
    // Imagen original simulada
    unsigned char imagen[3][3] = {
        {120, 100, 80},
        {60, 90, 200},
        {33, 66, 99}
    };

    // Clave simulada
    unsigned char clave[3][3] = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255}
    };

    // Resultado (imagen enmascarada)
    unsigned char resultado[3][3];

    // Enmascarar
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            resultado[i][j] = imagen[i][j] ^ clave[i][j];
        }
    }

    // Ahora desenmascaramos
    unsigned char recuperado[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            recuperado[i][j] = resultado[i][j] ^ clave[i][j];
        }
    }

    // Mostrar imagen recuperada
    cout << "\nImagen recuperada:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "Pixel " << i+1 << ": (";
        cout << int(recuperado[i][0]) << ", "
             << int(recuperado[i][1]) << ", "
             << int(recuperado[i][2]) << ")" << endl;
    }

    return 0;
}
