#include <iostream>

using namespace std;

int main()
{int N,i;
    i=1;
    cout << "Cuadrado perfecto" << endl;
    cout <<"Ingrese un numero"<<endl;
    cin>>N;
    while (true) {
        ++i;
        if(i*i==N){

        cout<<"Es cuadrado perfecto"<<endl;
            break;
        }
        if(i>N){
            cout<<"No es cuadrado"<<endl;
            break;
        }

    }
    return 0;
}
