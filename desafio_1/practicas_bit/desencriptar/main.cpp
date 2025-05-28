#include <QCoreApplication>
#include <QImage>
#include <iostream>

using namespace std;

// Funciones auxiliares
unsigned char* cargarImagen(QString ruta, int &w, int &h) {
    QImage imagen(ruta);

    if (imagen.isNull()) {
        cerr << "Error al cargar imagen: " << ruta.toStdString() << endl;
        return nullptr;
    }

    imagen = imagen.convertToFormat(QImage::Format_RGB888);
    w = imagen.width();
    h = imagen.height();

    unsigned char* datos = new unsigned char[w * h * 3];

    for (int y = 0; y < h; ++y) {
        const uchar* linea = imagen.scanLine(y);
        for (int x = 0; x < w * 3; ++x) {
            datos[y * w * 3 + x] = linea[x];
        }
    }

    return datos;
}

bool guardarImagen(unsigned char* pixelData, int w, int h, QString nombreSalida) {
    QImage output(w, h, QImage::Format_RGB888);

    for (int y = 0; y < h; ++y) {
        uchar* linea = output.scanLine(y);
        for (int x = 0; x < w * 3; ++x) {
            linea[x] = pixelData[y * w * 3 + x];
        }
    }

    return output.save(nombreSalida, "BMP");
}

// Función para aplicar XOR entre dos arreglos
void aplicarXOR(unsigned char* origen, unsigned char* clave, unsigned char* destino, int totalBytes) {
    for (int i = 0; i < totalBytes; ++i) {
        destino[i] = origen[i] ^ clave[i];
    }
}

// Función para rotar bits a la izquierda
void rotarIzquierda(unsigned char* datos, int bits, int totalBytes) {
    for (int i = 0; i < totalBytes; ++i) {
        datos[i] = (datos[i] << bits) | (datos[i] >> (8 - bits));
    }
}



int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QString rutaFinal = "Resultado_Final.bmp";   // Imagen encriptada
    QString rutaClave = "I_M.bmp";               // Imagen clave (IM)

    int wFinal = 0, hFinal = 0;
    int wClave = 0, hClave = 0;

    unsigned char* final = cargarImagen(rutaFinal, wFinal, hFinal);
    unsigned char* clave = cargarImagen(rutaClave, wClave, hClave);

    if (!final || !clave) {
        cerr << "Error al cargar imágenes." << endl;
        return -1;
    }

    if (wFinal != wClave || hFinal != hClave) {
        cerr << "Error: Las imágenes no tienen el mismo tamaño." << endl;
        delete[] final;
        delete[] clave;
        return -1;
    }

    int totalBytes = wFinal * hFinal * 3;
    unsigned char* temporal = new unsigned char[totalBytes];

    // 1. Deshacer último XOR (Resultado_Final ⊕ IM)
    aplicarXOR(final, clave, temporal, totalBytes);

    // 2. Deshacer la rotación derecha => rotar izquierda 3 bits
    rotarIzquierda(temporal, 3, totalBytes);

    // 3. Deshacer primer XOR (temporal ⊕ IM)
    aplicarXOR(temporal, clave, temporal, totalBytes);

    // 4. Guardar la imagen recuperada
    guardarImagen(temporal, wFinal, hFinal, "Imagen_Recuperada.bmp");
    cout << "✅ Imagen original recuperada exitosamente como 'Imagen_Recuperada.bmp'" << endl;

    // Liberar memoria
    delete[] final;
    delete[] clave;
    delete[] temporal;

    return 0;
}
