#include <QCoreApplication>
#include <QImage>
#include <QColor>
#include <iostream>
#include <bitset>

using namespace std;

// Funciones de manipulación de bits
unsigned char xorByte(unsigned char a, unsigned char b) {
    return a ^ b;
}

unsigned char rotarDerecha(unsigned char valor, int bits) {
    return (valor >> bits) | (valor << (8 - bits));
}

unsigned char rotarIzquierda(unsigned char valor, int bits) {
    return (valor << bits) | (valor >> (8 - bits));
}

unsigned char desplazarDerecha(unsigned char valor, int bits) {
    return valor >> bits;
}

unsigned char desplazarIzquierda(unsigned char valor, int bits) {
    return valor << bits;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Cargar la imagen BMP
    QImage imagen("ruta/a/tu/imagen.bmp");
    if (imagen.isNull()) {
        cerr << "Error al cargar la imagen." << endl;
        return -1;
    }

    // Aplicar operaciones a cada píxel
    for (int y = 0; y < imagen.height(); ++y) {
        for (int x = 0; x < imagen.width(); ++x) {
            QColor color = imagen.pixelColor(x, y);

            // Obtener componentes RGB
            unsigned char r = color.red();
            unsigned char g = color.green();
            unsigned char b = color.blue();

            // Aplicar operaciones bit a bit
            r = xorByte(r, 0xFF); // Ejemplo: invertir bits
            g = rotarDerecha(g, 2);
            b = desplazarIzquierda(b, 1);

            // Establecer el nuevo color
            imagen.setPixelColor(x, y, QColor(r, g, b));
        }
    }

    // Guardar la imagen modificada
    if (!imagen.save("imagen_modificada.bmp")) {
        cerr << "Error al guardar la imagen modificada." << endl;
        return -1;
    }

    cout << "Imagen modificada guardada exitosamente." << endl;

    return a.exec();
}
