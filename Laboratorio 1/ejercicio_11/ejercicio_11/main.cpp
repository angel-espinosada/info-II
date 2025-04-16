#include <iostream>

using namespace std;

int main()
{
    int N,i,result;
    cout << "Ingrese un numero para hacer tabla de multiplicar: " << endl;
    cin>>N;
    for (i = 1; i <= 10; ++i) {
        if(i<=10){
            result=i*N;
            cout<<i<<" x "<<N<<"="<<result<<endl;
        }

    }
    return 0;
}
