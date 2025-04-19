#include <iostream>

using namespace std;

int main()
{
    int N,hora, minutos, segundos;
    hora=0;minutos=0;segundos=0;
    cout << "Convertir a formato hora minutos y segundos" << endl;
    cout<<"Ingrese un numero: "<<endl;
    cin>>N;

    hora=N/3600;
    minutos=N%3600;
    segundos=minutos%60;
    minutos=minutos/60;

    cout<<hora<<":"<<minutos<<":"<<segundos<<endl;
    return 0;
}
