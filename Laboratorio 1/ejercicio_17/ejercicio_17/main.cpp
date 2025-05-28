#include <iostream>

using namespace std;

int main()
{
    int N, mayor;
    cout << "Programa que encuentra el numero mayor, hasta que se ingresa 0" << endl;
    cout<< "Ingrese un numero: "<<endl;
    cin>>N;
     mayor=N;
    while (true) {
        cin>>N;


        if (N==0)break;
        if(N>mayor){
            mayor=N;
        }
    }
        cout<<"El numero mayor es: "<<mayor<<endl;

    return 0;

}
