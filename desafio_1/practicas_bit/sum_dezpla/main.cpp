#include <QCoreApplication>
#include <QImage>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // --- Leer la semilla y cantidad de pixeles ---
    ifstream archivoM1("M1.txt");
    if (!archivoM1.is_open()) {
        cerr << "Error: No se pudo abrir M1.txt" << endl;
        return -1;
    }

    int semilla = 0;
    archivoM1 >> semilla;
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
    cout << "Semilla: " << semilla << ", Cantidad de pixeles: " << cantidadPixeles << endl;

    // --- Cargar imagen P1.bmp ---
    QImage imagenP1("P1.bmp");
    if (imagenP1.isNull()) {
        cerr << "Error al cargar P1.bmp" << endl;
        return -1;
    }
    imagenP1 = imagenP1.convertToFormat(QImage::Format_RGB888);

    int widthP1 = imagenP1.width();
    int heightP1 = imagenP1.height();

    // --- Cargar máscara M.bmp ---
    QImage mascara("M.bmp");
    if (mascara.isNull()) {
        cerr << "Error al cargar M.bmp" << endl;
        return -1;
    }
    mascara = mascara.convertToFormat(QImage::Format_RGB888);

    int widthM = mascara.width();
    int heightM = mascara.height();
    cout << "Tamaño de M.bmp: " << widthM << "x" << heightM << endl;

    if (widthM * heightM != cantidadPixeles) {
        cerr << "Error: Dimensiones de M.bmp no coinciden con cantidad de píxeles de M1.txt" << endl;
        return -1;
    }

    // --- Convertir P1 a arreglo dinámico ---
    unsigned char* pixelData = new unsigned char[widthP1 * heightP1 * 3];
    for (int y = 0; y < heightP1; ++y) {
        const uchar* line = imagenP1.scanLine(y);
        for (int x = 0; x < widthP1 * 3; ++x) {
            pixelData[y * widthP1 * 3 + x] = line[x];
        }
    }

    // --- Convertir M a arreglo dinámico ---
    unsigned char* mascaraData = new unsigned char[widthM * heightM * 3];
    for (int y = 0; y < heightM; ++y) {
        const uchar* line = mascara.scanLine(y);
        for (int x = 0; x < widthM * 3; ++x) {
            mascaraData[y * widthM * 3 + x] = line[x];
        }
    }

    // --- Extraer bloque desplazado ---
    unsigned char* bloqueDesplazado = new unsigned char[cantidadPixeles * 3];
    int inicio = semilla * 3;
    for (int i = 0; i < cantidadPixeles * 3; ++i) {
        bloqueDesplazado[i] = pixelData[inicio + i];
    }

    // --- Sumar bloqueDesplazado + mascaraData ---
    cout << "\nResultado de las sumas (primeros 5 píxeles):" << endl;
    for (int i = 0; i < 5 * 3; i += 3) {
        int r = int(bloqueDesplazado[i])   + int(mascaraData[i]);
        int g = int(bloqueDesplazado[i+1]) + int(mascaraData[i+1]);
        int b = int(bloqueDesplazado[i+2]) + int(mascaraData[i+2]);

        cout << "(" << r << ", " << g << ", " << b << ")" << endl;
    }

    // --- Liberar memoria ---
    delete[] pixelData;
    delete[] mascaraData;
    delete[] bloqueDesplazado;

    return 0;
}
