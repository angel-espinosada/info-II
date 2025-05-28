#include <iostream>
#include <bitset>
using namespace std;

int derecha(int value, int n) {
    const int byte = 8;
    return (value >> n) | (value << (byte - n));
}


int izq(int value, int n) {
    const int byte = 8;
    return (value << n) | (value >> (byte - n));
}

int main() {

    int numero = 58;

    // número original
    cout << "Numero original: " << numero << " (Binario: " <<bitset<8>(numero) << ")" <<endl;

    // aplico rotación hacia la derecha
    int rotacionDerecha = derecha(numero, 3); // Rotar 3 bits a la derecha
    cout << "Rotacion derecha (3 bits): " << rotacionDerecha << " (Binario: " << bitset<8>(rotacionDerecha) << ")" << endl;

    // aplico rotación hacia la izquierda
    int rotacionIzquierda = izq(numero, 3); // Rotar 3 bits a la izquierda
    cout << "Rotacion izquierda (3 bits): " << rotacionIzquierda << " (Binario: " << bitset<8>(rotacionIzquierda) << ")" << endl;

    return 0;
}
