#include <iostream>

using namespace std;

int main()
{int N,contador;
    contador=0;
    cout << "Numero primo" << endl;
    cout <<"Ingrese un numero: "<<endl;
    cin>>N;
    for (int i = 1; i <= N; ++i) {
        if(N%i==0){
        ++contador;
        }

    }
    if(contador==2){
        cout<<"Es primo"<<endl;

    }
    else{
        cout<<"No es primo"<<endl;
    }
    return 0;
}
