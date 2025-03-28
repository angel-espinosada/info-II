#include <iostream>

using namespace std;



    int main() {
        int n1, n2, residuo=0;


        cout << "Ingrese el valor de numero 1: ";
        cin >> n1;

        cout << "Ingrese el valor de numero 2: ";
        cin >> n2;


        residuo = n1 % n2;


        cout << "El residuo de la division " << n1<< "/" << n2 << " es: " << residuo << "\n";;

        return 0;
    }
