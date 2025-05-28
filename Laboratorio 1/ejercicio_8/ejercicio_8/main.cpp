#include <iostream>

using namespace std;

int main()
{
    int n,i,temp=1;
    cout << "Imprime numero factorial!" << endl;
    cout<<"Ingrese un numero: "<<endl;
    cin>>n;
    for (i=1; i<=n;i++){
        temp=temp*i;
    }
    cout <<"El factorial es: "<<temp<<endl;
    return 0;
}
