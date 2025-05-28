#include <iostream>
#include <bitset> // para imprimir en binario
using namespace std;

unsigned char xorByte(unsigned char a, unsigned char b) {
    return a ^ b;
}

unsigned char rotarIzquierda(unsigned char valor, int n) {
    return (valor << n) | (valor >> (8 - n));
}

unsigned char rotarDerecha(unsigned char valor, int n) {
    return (valor >> n) | (valor << (8 - n));
}

unsigned char desplazarIzquierda(unsigned char valor, int n) {
    return valor << n;
}

unsigned char desplazarDerecha(unsigned char valor, int n) {
    return valor >> n;
}

int main()
{
    unsigned char A = 172; // 10101100
    unsigned char B = 85;  // 01010101

    cout << "A = " << bitset<8>(A) << " (" << int(A) << ")" << endl;
    cout << "B = " << bitset<8>(B) << " (" << int(B) << ")" << endl;

    // XOR
    unsigned char resultadoXOR = xorByte(A, B);
    cout << "XOR  = " << bitset<8>(resultadoXOR) << " (" << int(resultadoXOR) << ")" << endl;

    // Rotar izquierda 2 bits
    unsigned char rotIzq = rotarIzquierda(A, 2);
    cout << "RotIzq(2) = " << bitset<8>(rotIzq) << " (" << int(rotIzq) << ")" << endl;

    // Rotar derecha 2 bits
    unsigned char rotDer = rotarDerecha(A, 2);
    cout << "RotDer(2) = " << bitset<8>(rotDer) << " (" << int(rotDer) << ")" << endl;

    // Desplazar izquierda 2 bits
    unsigned char desplIzq = desplazarIzquierda(A, 2);
    cout << "DesplIzq(2) = " << bitset<8>(desplIzq) << " (" << int(desplIzq) << ")" << endl;

    // Desplazar derecha 2 bits
    unsigned char desplDer = desplazarDerecha(A, 2);
    cout << "DesplDer(2) = " << bitset<8>(desplDer) << " (" << int(desplDer) << ")" << endl;
}
