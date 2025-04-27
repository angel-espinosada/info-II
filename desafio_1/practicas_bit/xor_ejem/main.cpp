#include <QCoreApplication>
#include <QImage>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Cargar la imagen original
    QImage imagenOriginal("I_O.bmp");
    if (imagenOriginal.isNull()) {
        cerr << "Error: No se pudo cargar I_O.bmp" << endl;
        return -1;
    }

    // Cargar la imagen IM
    QImage imagenIM("I_M.bmp");
    if (imagenIM.isNull()) {
        cerr << "Error: No se pudo cargar I_M.bmp" << endl;
        return -1;
    }

    // Verificar que las dimensiones coincidan
    if (imagenOriginal.width() != imagenIM.width() || imagenOriginal.height() != imagenIM.height()) {
        cerr << "Error: Las dimensiones de las imágenes no coinciden" << endl;
        return -1;
    }

    // Convertir ambas imágenes a formato RGB888
    imagenOriginal = imagenOriginal.convertToFormat(QImage::Format_RGB888);
    imagenIM = imagenIM.convertToFormat(QImage::Format_RGB888);

    int width = imagenOriginal.width();
    int height = imagenOriginal.height();

    // Crear imagen resultante
    QImage imagenXOR(width, height, QImage::Format_RGB888);

    // Hacer XOR pixel a pixel
    for (int y = 0; y < height; ++y) {
        const uchar* lineaOriginal = imagenOriginal.scanLine(y);
        const uchar* lineaIM = imagenIM.scanLine(y);
        uchar* lineaResultado = imagenXOR.scanLine(y);

        for (int x = 0; x < width * 3; ++x) { // *3 porque son 3 canales (RGB)
            lineaResultado[x] = lineaOriginal[x] ^ lineaIM[x];
        }
    }

    // Guardar la imagen XOR como P1.bmp
    if (imagenXOR.save("P1.bmp")) {
        cout << "Imagen P1.bmp generada exitosamente." << endl;
    } else {
        cerr << "Error al guardar P1.bmp" << endl;
        return -1;
    }

    return 0;
}
