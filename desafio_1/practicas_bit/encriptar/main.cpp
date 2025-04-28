#include <QCoreApplication>
#include <QImage>
#include <iostream>
#include <fstream>

using namespace std;

// -------- FUNCIONES ---------
// Cargar imagen BMP
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

// Guardar arreglo como imagen BMP
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

// Aplicar XOR entre dos imágenes
void aplicarXOR(unsigned char* origen, unsigned char* clave, unsigned char* destino, int totalBytes) {
    for (int i = 0; i < totalBytes; ++i) {
        destino[i] = origen[i] ^ clave[i];
    }
}

// Rotar bits a la derecha
void rotarDerecha(unsigned char* datos, int bits, int totalBytes) {
    for (int i = 0; i < totalBytes; ++i) {
        datos[i] = (datos[i] >> bits) | (datos[i] << (8 - bits));
    }
}

// Enmascarar y guardar .txt
void enmascarar(unsigned char* imagen, unsigned char* mascara, int wMascara, int hMascara, int offset, QString nombreArchivo) {
    ofstream archivo(nombreArchivo.toStdString());
    if (!archivo.is_open()) {
        cerr << "Error al crear archivo " << nombreArchivo.toStdString() << endl;
        return;
    }

    int totalValores = wMascara * hMascara * 3;
    archivo << offset << endl;  // Escribir semilla

    for (int i = 0; i < totalValores; i += 3) {
        int r = imagen[(i + offset) + 0] + mascara[i + 0];
        int g = imagen[(i + offset) + 1] + mascara[i + 1];
        int b = imagen[(i + offset) + 2] + mascara[i + 2];

        archivo << r << " " << g << " " << b << endl;
    }

    archivo.close();
}

// ----------- MAIN -----------
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QString rutaOriginal = "I_O.bmp";  // Imagen original
    QString rutaClave = "I_M.bmp";     // Imagen clave (IM)
    QString rutaMascara = "M.bmp";     // Máscara (M)

    int wOriginal = 0, hOriginal = 0;
    int wClave = 0, hClave = 0;
    int wMascara = 0, hMascara = 0;

    // Cargar imágenes
    unsigned char* original = cargarImagen(rutaOriginal, wOriginal, hOriginal);
    unsigned char* clave = cargarImagen(rutaClave, wClave, hClave);
    unsigned char* mascara = cargarImagen(rutaMascara, wMascara, hMascara);

    if (!original || !clave || !mascara) {
        cerr << "Error al cargar alguna imagen." << endl;
        return -1;
    }

    int totalBytes = wOriginal * hOriginal * 3;
    unsigned char* temporal = new unsigned char[totalBytes];

    bool salir = false;

    while (!salir) {
        cout << "\n======= MENU =======" << endl;
        cout << "1. Aplicar XOR (IO x IM)" << endl;
        cout << "2. Rotar 3 bits a la derecha" << endl;
        cout << "3. Aplicar XOR nuevamente (resultado x IM)" << endl;
        cout << "4. Enmascarar y generar M1.txt" << endl;
        cout << "5. Enmascarar y generar M2.txt" << endl;
        cout << "6. Guardar imagen procesada" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione opcion: ";

        int opcion;
        cin >> opcion;

        switch (opcion) {
        case 1:
            aplicarXOR(original, clave, temporal, totalBytes);
            guardarImagen(temporal, wOriginal, hOriginal, "P1.bmp");
            cout << "Se creó P1.bmp (XOR inicial)." << endl;
            break;
        case 2:
            rotarDerecha(temporal, 3, totalBytes);
            guardarImagen(temporal, wOriginal, hOriginal, "P2.bmp");
            cout << "Se creó P2.bmp (Rotación 3 bits derecha)." << endl;
            break;
        case 3:
            aplicarXOR(temporal, clave, temporal, totalBytes);
            guardarImagen(temporal, wOriginal, hOriginal, "P3.bmp");
            cout << "Se creó P3.bmp (XOR final)." << endl;
            break;
        case 4: {
            int desplazamiento;
            cout << "Ingrese desplazamiento (semilla) para M1.txt: ";
            cin >> desplazamiento;
            enmascarar(temporal, mascara, wMascara, hMascara, desplazamiento, "M1.txt");
            cout << "Se creó M1.txt." << endl;
            break;
        }
        case 5: {
            int desplazamiento;
            cout << "Ingrese desplazamiento (semilla) para M2.txt: ";
            cin >> desplazamiento;
            enmascarar(temporal, mascara, wMascara, hMascara, desplazamiento, "M2.txt");
            cout << "Se creó M2.txt." << endl;
            break;
        }
        case 6:
            guardarImagen(temporal, wOriginal, hOriginal, "Resultado_Final.bmp");
            cout << "Se guardó Resultado_Final.bmp." << endl;
            break;
        case 7:
            salir = true;
            break;
        default:
            cout << "Opción inválida." << endl;
        }
    }

    // Liberar memoria
    delete[] original;
    delete[] clave;
    delete[] mascara;
    delete[] temporal;

    cout << "Programa finalizado." << endl;
    return 0;
}
