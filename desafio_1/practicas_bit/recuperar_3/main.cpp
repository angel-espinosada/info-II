#include <QCoreApplication>
#include <QImage>
#include <iostream>

using namespace std;

// Función XOR entre dos bytes
unsigned char xorByte(unsigned char a, unsigned char b) {
    return a ^ b;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 1. Cargar la imagen rotada y la imagen IM
    QImage imagenRotada("Paso2_Rotado_P1.bmp");
    QImage imagenIM("I_M.bmp");

    if (imagenRotada.isNull() || imagenIM.isNull()) {
        cerr << "Error al cargar las imágenes." << endl;
        return -1;
    }

    imagenRotada = imagenRotada.convertToFormat(QImage::Format_RGB888);
    imagenIM = imagenIM.convertToFormat(QImage::Format_RGB888);

    int width = imagenRotada.width();
    int height = imagenRotada.height();

    if (width != imagenIM.width() || height != imagenIM.height()) {
        cerr << "Las imágenes no tienen el mismo tamaño." << endl;
        return -1;
    }

    // 2. Crear imagen para almacenar la imagen reconstruida
    QImage imagenRecuperada(width, height, QImage::Format_RGB888);

    // 3. Aplicar XOR píxel a píxel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor colorRotado = imagenRotada.pixelColor(x, y);
            QColor colorIM = imagenIM.pixelColor(x, y);

            int r = xorByte(colorRotado.red(), colorIM.red());
            int g = xorByte(colorRotado.green(), colorIM.green());
            int b = xorByte(colorRotado.blue(), colorIM.blue());

            imagenRecuperada.setPixelColor(x, y, QColor(r, g, b));
        }
    }

    // 4. Guardar la imagen reconstruida
    if (!imagenRecuperada.save("Paso3_Imagen_Recuperada.bmp")) {
        cerr << "Error al guardar la imagen reconstruida." << endl;
        return -1;
    }

    cout << "Tercer paso completado: Imagen reconstruida guardada como Paso3_Imagen_Recuperada.bmp" << endl;

    return 0;
}
