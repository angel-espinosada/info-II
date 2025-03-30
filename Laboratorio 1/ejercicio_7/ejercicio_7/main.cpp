#include <iostream>

using namespace std;

int main()
{
    int n,i,temp=0;
    cout << "Suma de numeros!" << endl;
    cout<<"Ingrese un numero"<<endl;
    cin>>n;
    for (i=0;i<=n;i++){
        temp=temp+i;
//cout<<"Numero"<<temp<<endl;

    }
    cout<<"La suma de los numeros del 0 al "<<n<<" es: "<<temp<<endl;
    return 0;
}
