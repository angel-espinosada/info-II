#include <QCoreApplication>
#include <QImage>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // --- Leer la semilla y la cantidad de pixeles ---
    ifstream archivoM1("M1.txt");
    if (!archivoM1.is_open()) {
        cerr << "Error: No se pudo abrir M1.txt" << endl;
        return -1;
    }

    int semilla = 0;
    archivoM1 >> semilla;
    cout << "Semilla: " << semilla << endl;

    int contadorValores = 0, temp = 0;
    while (archivoM1 >> temp) {
        contadorValores++;
    }
    archivoM1.close();

    if (contadorValores % 3 != 0) {
        cerr << "Error: Archivo M1.txt no tiene tripletas RGB completas." << endl;
        return -1;
    }

    int cantidadPixeles = contadorValores / 3;
    cout << "Cantidad de píxeles que debemos procesar: " << cantidadPixeles << endl;

    // --- Cargar imagen P1.bmp ---
    QImage imagenP1("P1.bmp");
    if (imagenP1.isNull()) {
        cerr << "Error al cargar P1.bmp" << endl;
        return -1;
    }

    imagenP1 = imagenP1.convertToFormat(QImage::Format_RGB888);

    int width = imagenP1.width();
    int height = imagenP1.height();
    cout << "Tamaño imagen P1: " << width << " x " << height << endl;

    // --- Convertir imagen a arreglo lineal dinámico ---
    unsigned char* pixelData = new unsigned char[width * height * 3];

    for (int y = 0; y < height; ++y) {
        const uchar* line = imagenP1.scanLine(y);
        for (int x = 0; x < width * 3; ++x) {
            pixelData[y * width * 3 + x] = line[x];
        }
    }

    // --- Extraer los pixeles desplazados ---
    unsigned char* bloqueDesplazado = new unsigned char[cantidadPixeles * 3];

    int inicio = semilla * 3; // Recuerda, cada pixel tiene 3 valores
    for (int i = 0; i < cantidadPixeles * 3; ++i) {
        bloqueDesplazado[i] = pixelData[inicio + i];
    }

    // --- Mostrar los primeros 5 píxeles extraídos ---
    cout << "\nPrimeros 5 píxeles extraídos:" << endl;
    for (int i = 0; i < 5 * 3; i += 3) {
        cout << "("
             << int(bloqueDesplazado[i]) << ", "
             << int(bloqueDesplazado[i+1]) << ", "
             << int(bloqueDesplazado[i+2]) << ")" << endl;
    }

    // --- Libera la memoria ---
    delete[] pixelData;
    delete[] bloqueDesplazado;

    return 0;
}
