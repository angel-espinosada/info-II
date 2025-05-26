#include <iostream>
#include<enrutador.h>
#include<red.h>

using namespace std;

int main()
{

    Red miRed;

    // Agregar enrutadores
    miRed.agregarEnrutador("A");
    miRed.agregarEnrutador("B");
    miRed.agregarEnrutador("C");
    miRed.agregarEnrutador("D");

    // Conectar enrutadores
    miRed.conectarEnrutadores("A", "B", 4);
    miRed.conectarEnrutadores("A", "C", 3);
    miRed.conectarEnrutadores("B", "D", 2);
    miRed.conectarEnrutadores("C", "D", 1);

    cout << "Estado de la red:\n";
    miRed.mostrarRed();

    // Eliminar un enrutador
    miRed.eliminarEnrutador("C");

    cout << "Red despues de eliminar C:\n";
    miRed.mostrarRed();

    return 0;
}
