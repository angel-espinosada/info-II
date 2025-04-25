#include <iostream>
#include <bitset>
using namespace std;

// Funciones bit a bit
unsigned char xorByte(unsigned char a, unsigned char b) {
    return a ^ b;
}
unsigned char rotarDerecha(unsigned char valor, int bits) {
    return (valor >> bits) | (valor << (8 - bits));
}
unsigned char rotarIzquierda(unsigned char valor, int bits) {
    return (valor << bits) | (valor >> (8 - bits));
}

int main() {
    //  Simulación de una imagen: 3 píxeles = 9 bytes
    unsigned char pixeles[] = {
        100, 150, 200,
        50,  80,  120,
        255, 0,   128
    };

    unsigned char clave = 0xAA; // 10101010
    int numPixeles = sizeof(pixeles) / sizeof(pixeles[0]);

    cout << "PIXELES ORIGINALES:\n";
    for (int i = 0; i < numPixeles; ++i) {
        cout << "[" << i << "] = "
             << int(pixeles[i]) << " -> "
             << bitset<8>(pixeles[i]) << endl;
    }

    // Aplicar XOR con la clave a cada canal
    for (int i = 0; i < numPixeles; ++i) {
        pixeles[i] = xorByte(pixeles[i], clave);
    }

    cout << "\n Después de XOR con 0xAA:\n";
    for (int i = 0; i < numPixeles; ++i) {
        cout << "[" << i << "] = "
             << int(pixeles[i]) << " -> "
             << bitset<8>(pixeles[i]) << endl;
    }

    // Podrías aplicar también rotación, desplazamiento, etc.

    return 0;
}
