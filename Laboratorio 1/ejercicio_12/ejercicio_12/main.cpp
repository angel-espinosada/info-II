#include <iostream>

using namespace std;

int main()
{
    int N,result,i;
    result=1;

    cout << "Programa que eleva la potencia hasta 5 veces" << endl;
    cin>>N;
    for (i = 1; i <= 5; ++i) {
        result=result*N;
        cout<<N<<"*"<<"="<<result<<endl;
    }

    return 0;
}
