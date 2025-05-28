#include <iostream>

using namespace std;

int main()
{
    char letra;

    cout << "Convertir a mayuscula o viceversa" << endl;
    cout<<"ingresar una letra"<<endl;
    cin>>letra;
    if(letra>='a'&&letra<='z'){
        letra=letra - 32;
        cout<<"Letra convertida: "<<letra<<endl;

    }
    else if(letra>='A'&&letra<='Z') {
            letra=letra + 32;
            cout<<"Letra convertida: "<<letra<<endl;
        }
    return 0;
}
