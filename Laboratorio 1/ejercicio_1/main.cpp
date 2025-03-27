#include <iostream>

using namespace std;

int main()
{
    int a, b, residuo;
    cout << "Ingrese el valor de a: ";
    cin >> a;

    cout << "Ingrese el valor de b: ";
    cin >> b;


    residuo = a % b;
    cout << "El residuo de la division " << a << "/" << b << " es: " << residuo << "\n";;

    return 0;
}
