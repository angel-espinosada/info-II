#include <iostream>

using namespace std;

int main()
{
    int N,suma;
    suma=0;
    cout << "Ingresar numeros hasta que ingreses el 0, luego entregas las suma de ellos" << endl;
    cout<<"Ingrese un numero: "<<endl;
    cin>>N;
    while (N!=0) {
        suma=suma+N;
        cin>>N;
    }
    cout<<"La suma es: "<<suma<<endl;
    return 0;
}
