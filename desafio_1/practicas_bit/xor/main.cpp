#include <iostream>
#include <bitset>
using namespace std;
int main() {
    // Definir dos números enteros
    int numero1 = 15;  // En binario: 00001111
    int numero2 = 240; // En binario: 11110000

    // Aplicar XOR entre los números
    int resultado = numero1 ^ numero2;

    // Mostrar los resultados
cout << "Numero 1: " << numero1 << " (Binario: " << bitset<8>(numero1) << ")" <<endl;
cout << "Numero 2: " << numero2 << " (Binario: " << bitset<8>(numero2) << ")" <<endl;
cout << "Resultado XOR: " << resultado << " (Binario: " << bitset<8>(resultado) << ")" <<endl;

    return 0;
}
