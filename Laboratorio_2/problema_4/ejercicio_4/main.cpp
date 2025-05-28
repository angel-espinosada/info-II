#include <iostream>

using namespace std;

int main()
{
    char palabra[100];
    int number,nuevo=0;

    cout << "Cadena a entero" << endl;
    cout << "Ingrese la cadena: " << endl;
    cin>>palabra;

    for (int i = 0; palabra[i]!= '\0'; ++i) {

        number=palabra[i]-'0';
        nuevo=nuevo*10+number;
    }
    cout<<nuevo<<endl;
    return 0;
}
