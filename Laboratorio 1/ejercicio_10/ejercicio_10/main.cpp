#include <iostream>

using namespace std;

int main()
{
    cout << "Progrma que imprime los multiplos del 1 al 100" << endl;

    int N,i;
    cout<<"ingrese un numero: "<<endl;
    cin>>N;
    for(int i=1; i<=100;i++){
        if (i%N==0){
            cout << i << endl;
        }
    }

    return 0;
}
