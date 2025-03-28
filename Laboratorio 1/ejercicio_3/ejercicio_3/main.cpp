#include <iostream>

using namespace std;

int main()
{
    int x, y;
    cout << "Ingrese el valor de X: ";
    cin >> x;
    cout << "Ingrese el valor de Y: ";
    cin >> y;

    if (x > y) {
        cout << "El mayor es " << x << "\n";
    } else if (y > x) {
        cout << "El mayor es " << y << "\n";;
    } else {
        cout << "Ambos números son iguales" << "\n";;
    }

    return 0;
}
