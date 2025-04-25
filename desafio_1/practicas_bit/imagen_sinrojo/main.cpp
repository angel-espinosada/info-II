#include <QCoreApplication>
#include <QImage>
#include <QColor>
#include <iostream>
#include <bitset>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QImage imagen("sample.bmp"); // Asegúrate que esta imagen esté en tu carpeta del proyecto o pon ruta completa

    if (imagen.isNull()) {
        cerr << "Error: No se pudo cargar la imagen." << endl;
        return -1;
    }

    int ancho = imagen.width();
    int alto = imagen.height();
    int totalPixeles = ancho * alto;

    cout << "La imagen tiene " << totalPixeles << " píxeles ("
         << ancho << " x " << alto << ")" << endl << endl;

    //  Eliminar el rojo de todos los píxeles
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            QColor color = imagen.pixelColor(x, y);

            int r = 0; // Eliminamos el rojo
            int g = color.green();
            int b = color.blue();

            imagen.setPixelColor(x, y, QColor(r, g, b));
        }
    }

    // ✅ Guardar la nueva imagen
    QString rutaGuardado = "G:/Mi unidad/UdeA/imagen_sin_rojo.bmp";
    bool exito = imagen.save(rutaGuardado);

    if (exito) {
        cout << "Imagen modificada guardada exitosamente en: " << rutaGuardado.toStdString() << endl;
    } else {
        cerr << "Error al guardar la imagen modificada." << endl;
    }

    return 0;
}
