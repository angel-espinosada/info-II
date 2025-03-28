#include <iostream>

using namespace std;

int main()
{
    int num;
    cout << "Ingrese un numero: ";
    cin >> num;

    if (num % 2 == 0) {
        cout << num << " es par" << "\n";
    } else {
        cout << num << " es impar" << "\n";
    }

    return 0;
}
