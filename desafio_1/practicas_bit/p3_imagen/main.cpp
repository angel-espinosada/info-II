#include <QCoreApplication>
#include <QImage>
#include <iostream>

using namespace std;

// Función para aplicar XOR
unsigned char aplicarXOR(unsigned char a, unsigned char b) {
    return a ^ b;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Cargar P2.bmp
    QImage imagenP2("P2.bmp");
    if (imagenP2.isNull()) {
        cerr << "Error: No se pudo cargar P2.bmp" << endl;
        return -1;
    }

    // Cargar I_M.bmp
    QImage imagenIM("I_M.bmp");
    if (imagenIM.isNull()) {
        cerr << "Error: No se pudo cargar I_M.bmp" << endl;
        return -1;
    }

    // Verificar tamaños
    if (imagenP2.width() != imagenIM.width() || imagenP2.height() != imagenIM.height()) {
        cerr << "Error: Las imágenes P2.bmp e I_M.bmp no tienen las mismas dimensiones" << endl;
        return -1;
    }

    // Convertir ambas a RGB888
    imagenP2 = imagenP2.convertToFormat(QImage::Format_RGB888);
    imagenIM = imagenIM.convertToFormat(QImage::Format_RGB888);

    int width = imagenP2.width();
    int height = imagenP2.height();

    // Crear imagen P3.bmp
    QImage imagenP3(width, height, QImage::Format_RGB888);

    // Aplicar XOR
    for (int y = 0; y < height; ++y) {
        const uchar* lineaP2 = imagenP2.scanLine(y);
        const uchar* lineaIM = imagenIM.scanLine(y);
        uchar* lineaP3 = imagenP3.scanLine(y);

        for (int x = 0; x < width * 3; ++x) { // *3 canales
            lineaP3[x] = aplicarXOR(lineaP2[x], lineaIM[x]);
        }
    }

    // Guardar imagen P3.bmp
    if (imagenP3.save("P3.bmp")) {
        cout << "Imagen P3.bmp generada exitosamente." << endl;
    } else {
        cerr << "Error al guardar P3.bmp" << endl;
        return -1;
    }

    return 0;
}
