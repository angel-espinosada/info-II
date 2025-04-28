#include <QCoreApplication>
#include <QImage>
#include <iostream>

using namespace std;

// Función para rotar 3 bits a la izquierda
unsigned char rotarIzquierda(unsigned char valor, int bits) {
    return (valor << bits) | (valor >> (8 - bits));
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 1. Cargar imagen resultado del paso anterior
    QImage imagenPaso1("Paso1_XOR_P2.bmp");

    if (imagenPaso1.isNull()) {
        cerr << "Error al cargar Paso1_XOR_P2.bmp." << endl;
        return -1;
    }

    imagenPaso1 = imagenPaso1.convertToFormat(QImage::Format_RGB888);

    int width = imagenPaso1.width();
    int height = imagenPaso1.height();

    // 2. Crear imagen de salida para rotada
    QImage imagenRotada(width, height, QImage::Format_RGB888);

    // 3. Aplicar rotación 3 bits a la izquierda pixel a pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor color = imagenPaso1.pixelColor(x, y);

            int r = rotarIzquierda(color.red(), 3);
            int g = rotarIzquierda(color.green(), 3);
            int b = rotarIzquierda(color.blue(), 3);

            imagenRotada.setPixelColor(x, y, QColor(r, g, b));
        }
    }

    // 4. Guardar imagen rotada
    if (!imagenRotada.save("Paso2_Rotado_P1.bmp")) {
        cerr << "Error al guardar la imagen rotada." << endl;
        return -1;
    }

    cout << "Segundo paso completado: Imagen rotada 3 bits a la izquierda y guardada como Paso2_Rotado_P1.bmp" << endl;

    return 0;
}
