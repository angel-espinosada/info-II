#include <QCoreApplication>
#include <QImage>
#include <iostream>

using namespace std;

// Función XOR simple
unsigned char xorByte(unsigned char a, unsigned char b) {
    return a ^ b;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 1. Cargar imágenes
    QImage imagenP3("P3.bmp");
    QImage imagenIM("I_M.bmp");

    if (imagenP3.isNull() || imagenIM.isNull()) {
        cerr << "Error al cargar las imágenes." << endl;
        return -1;
    }

    imagenP3 = imagenP3.convertToFormat(QImage::Format_RGB888);
    imagenIM = imagenIM.convertToFormat(QImage::Format_RGB888);

    int width = imagenP3.width();
    int height = imagenP3.height();

    // Verificar que las dimensiones coincidan
    if (width != imagenIM.width() || height != imagenIM.height()) {
        cerr << "Las imágenes no tienen el mismo tamaño." << endl;
        return -1;
    }

    // 2. Crear imagen de salida
    QImage imagenXOR(width, height, QImage::Format_RGB888);

    // 3. Aplicar XOR píxel a píxel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor colorP3 = imagenP3.pixelColor(x, y);
            QColor colorIM = imagenIM.pixelColor(x, y);

            int r = xorByte(colorP3.red(), colorIM.red());
            int g = xorByte(colorP3.green(), colorIM.green());
            int b = xorByte(colorP3.blue(), colorIM.blue());

            imagenXOR.setPixelColor(x, y, QColor(r, g, b));
        }
    }

    // 4. Guardar imagen resultado
    if (!imagenXOR.save("Paso1_XOR_P2.bmp")) {
        cerr << "Error al guardar la imagen XOR." << endl;
        return -1;
    }

    cout << "Primer paso completado: XOR aplicado y guardado como Paso1_XOR_P2.bmp" << endl;

    return 0;
}
