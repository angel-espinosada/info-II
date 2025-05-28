#include <QCoreApplication>
#include <QImage>
#include <QColor>
#include <iostream>
#include <bitset>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QImage imagen("sample.bmp"); // Asegúrate de que esté bien ubicada
    if (imagen.isNull()) {
        cerr << "Error: No se pudo cargar la imagen." << endl;
        return -1;
    }

    int ancho = imagen.width();
    int alto = imagen.height();
    int totalPixeles = ancho * alto;

    cout << "La imagen tiene " << totalPixeles << " píxeles ("
         << ancho << " x " << alto << ")" << endl << endl;

    // Mostrar los primeros 10 píxeles
    int contador = 0;
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            QColor color = imagen.pixelColor(x, y);

            int r = color.red();
            int g = color.green();
            int b = color.blue();

            cout << "Pixel (" << x << ", " << y << "):" << endl;
            cout << "  R = " << r << " (" << bitset<8>(r) << ")" << endl;
            cout << "  G = " << g << " (" << bitset<8>(g) << ")" << endl;
            cout << "  B = " << b << " (" << bitset<8>(b) << ")" << endl;
            cout << "-----------------------------" << endl;

            contador++;
            if (contador >= 10) break; // Solo mostrar los primeros 10 píxeles
        }
        if (contador >= 10) break;
    }

    return 0;
}
