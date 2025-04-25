#include <iostream>
#include<bitset>

using namespace std;
// XOR entre dos bytes
unsigned char xorByte(unsigned char a, unsigned char b) {
    return a ^ b;
}

// Rotar bits a la derecha
unsigned char rotarDerecha(unsigned char valor, int bits) {
    return (valor >> bits) | (valor << (8 - bits));
}

// Rotar bits a la izquierda
unsigned char rotarIzquierda(unsigned char valor, int bits) {
    return (valor << bits) | (valor >> (8 - bits));
}

// Desplazar a la derecha (rellena con ceros)
unsigned char desplazarDerecha(unsigned char valor, int bits) {
    return valor >> bits;
}

//  Desplazar a la izquierda (rellena con ceros)
unsigned char desplazarIzquierda(unsigned char valor, int bits) {
    return valor << bits;
}

int main()
{
    unsigned char ejemplo = 0b10110010;
    unsigned char ff = 0xFF;

    cout << "Original:          " << bitset<8>(ejemplo) << endl;
     cout << "0xFF en binario es: " << bitset<8>(ff) << endl;
    cout << "XOR con 0xFF:      " << bitset<8>(xorByte(ejemplo, 0xFF)) << endl;
    cout << "Rotar derecha 3:   " << bitset<8>(rotarDerecha(ejemplo, 3)) << endl;
    cout << "Rotar izquierda 2: " << bitset<8>(rotarIzquierda(ejemplo, 2)) << endl;
    cout << "dezplamiento 2: " << bitset<8>(desplazarDerecha(ejemplo, 2)) << endl;
    return 0;
}
