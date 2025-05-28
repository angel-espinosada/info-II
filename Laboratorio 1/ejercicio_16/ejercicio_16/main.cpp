#include <iostream>

using namespace std;

int main()
{
    int N,suma,contador;
    float promedio;
    suma=0;
    contador=0;
    cout << "Ingresar numeros hasta que ingreses el 0, luego entrega el promedio de ellos" << endl;
    cout<<"Ingrese un numero: "<<endl;
    cin>>N;
    while (N!=0) {
        suma+=N;
        contador++;
        cin>>N;
    }

    if(contador>0){

        float promedio =(float)suma/contador;
        cout<<"La suma es: "<<promedio<<endl;
    }
    else{
        cout<<"No se ingresaron numeros"<<endl;
    }
    return 0;
}
