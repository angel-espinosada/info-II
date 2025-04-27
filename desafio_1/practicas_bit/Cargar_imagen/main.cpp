#include <QCoreApplication>
#include <QImage>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString rutaImagen = "I_O.bmp"; // Imagen de entrada
    QImage imagen(rutaImagen);

    if (imagen.isNull()) {
        cerr << "Error: no se pudo cargar la imagen " << rutaImagen.toStdString() << endl;
        return -1;
    }

    // Convertir a RGB888 (sin transparencia)
    imagen = imagen.convertToFormat(QImage::Format_RGB888);

    int width = imagen.width();
    int height = imagen.height();
    cout << "Ancho: " << width << " | Alto: " << height << endl;

    // Crear memoria dinámica para guardar los píxeles
    unsigned char* pixels = new unsigned char[width * height * 3];

    // Copiar la imagen al arreglo dinámico
    for (int y = 0; y < height; ++y) {
        const uchar* line = imagen.scanLine(y);
        for (int x = 0; x < width * 3; ++x) {
            pixels[y * width * 3 + x] = line[x];
        }
    }

    cout << "Imagen cargada exitosamente en arreglo dinámico!" << endl;

    // --- Contar valores de M1.txt ---
    ifstream archivoCuenta("M1.txt");

    if (!archivoCuenta.is_open()) {
        cerr << "Error: no se pudo abrir M1.txt" << endl;
        delete[] pixels;
        return -1;
    }

    int semilla;
    archivoCuenta >> semilla;

    int contador = 0;
    int temp;
    while (archivoCuenta >> temp) {
        contador++;
    }
    archivoCuenta.close();

    cout << "Cantidad de valores leídos: " << contador << endl;

    if (contador % 3 != 0) {
        cerr << "Error: El archivo no contiene tripletas completas RGB" << endl;
        delete[] pixels;
        return -1;
    }

    int cantidadPixelesClave = contador / 3;
    cout << "Cantidad de píxeles disponibles en clave: " << cantidadPixelesClave << endl;

    // --- Cargar valores reales de clave ---
    ifstream archivoClave("M1.txt");

    if (!archivoClave.is_open()) {
        cerr << "Error: no se pudo abrir M1.txt para leer valores" << endl;
        delete[] pixels;
        return -1;
    }

    archivoClave >> semilla; // leer semilla otra vez

    unsigned char* clave = new unsigned char[cantidadPixelesClave * 3];

    for (int i = 0; i < cantidadPixelesClave * 3; ++i) {
        int valor;
        archivoClave >> valor;
        clave[i] = static_cast<unsigned char>(valor);
    }

    archivoClave.close();
    cout << "Clave leída exitosamente!" << endl;

    // --- Aplicar XOR entre imagen y clave ---
    for (int i = 0; i < cantidadPixelesClave * 3; ++i) {
        pixels[i] = pixels[i] ^ clave[i];
    }
    cout << "XOR aplicado exitosamente!" << endl;

    // --- Guardar imagen modificada ---
    QImage imagenModificada(width, height, QImage::Format_RGB888);

    for (int y = 0; y < height; ++y) {
        uchar* line = imagenModificada.scanLine(y);
        memcpy(line, &pixels[y * width * 3], width * 3);
    }

    if (imagenModificada.save("imagen_modificada.bmp")) {
        cout << "Imagen modificada guardada exitosamente!" << endl;
    } else {
        cerr << "Error al guardar la imagen modificada!" << endl;
    }

    // --- Liberar memoria ---
    delete[] pixels;
    delete[] clave;

    return 0;
}
