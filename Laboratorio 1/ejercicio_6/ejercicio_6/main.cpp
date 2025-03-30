#include <iostream>

using namespace std;

int main()
{
    int a, b, i,temp=1;
    cout << "Potencia sin librerias" << endl;
    cout<< "Ingrese un numero"<<endl;
    cin >>a;
    cout<< "Ingrese la potencia"<<endl;
    cin >>b;
    for (i=0;i<b;i++){

        temp*=a;

    }
cout<<"La potencia es: "<<temp<<endl;
    return 0;
}

