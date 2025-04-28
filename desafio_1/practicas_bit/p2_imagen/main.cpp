#include <QCoreApplication>
#include <QImage>
#include <iostream>

using namespace std;

// Función para rotar bits 3 posiciones a la derecha
unsigned char rotarDerecha(unsigned char valor, int bits) {
    return (valor >> bits) | (valor << (8 - bits));
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Cargar la imagen P1.bmp
    QImage imagenP1("P1.bmp");
    if (imagenP1.isNull()) {
        cerr << "Error: No se pudo cargar P1.bmp" << endl;
        return -1;
    }

    // Convertir a formato RGB888
    imagenP1 = imagenP1.convertToFormat(QImage::Format_RGB888);

    int width = imagenP1.width();
    int height = imagenP1.height();

    // Crear imagen nueva para P2
    QImage imagenP2(width, height, QImage::Format_RGB888);

    // Recorrer y rotar los bits de cada canal
    for (int y = 0; y < height; ++y) {
        const uchar* lineaP1 = imagenP1.scanLine(y);
        uchar* lineaP2 = imagenP2.scanLine(y);

        for (int x = 0; x < width * 3; ++x) { // *3 por los 3 canales (R, G, B)
            lineaP2[x] = rotarDerecha(lineaP1[x], 3); // Rotar 3 bits
        }
    }

    // Guardar imagen P2.bmp
    if (imagenP2.save("P2.bmp")) {
        cout << "Imagen P2.bmp creada exitosamente (rotada 3 bits a la derecha)." << endl;
    } else {
        cerr << "Error al guardar P2.bmp" << endl;
        return -1;
    }

    return 0;
}
