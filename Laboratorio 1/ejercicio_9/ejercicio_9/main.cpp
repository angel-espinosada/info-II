#include <iostream>

using namespace std;

int main()
{
    float N,a,p;
    float pi;
    pi=3.1416;
    cout << "Ingrese el radio del circulo: " << endl;
    cin>>N;
    p=2*pi*(N);
    a=(N*N)*pi;
    cout<<"El perimetro del circulo es: "<<p<<endl;
    cout<<"El area del ciculos es: "<<a<<endl;
    return 0;
}
