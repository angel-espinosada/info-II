#include <iostream>

using namespace std;

int main()
{int N,original, invertir;
    invertir=0;
    cout << "Numero palindromo" << endl;
    cout <<"Ingresa un numero: "<<endl;
    cin>>N;
    original=N;
    while(N>0)
    {
        int num =N%10;
        invertir=invertir*10+num;
        N=N/10;




    }
    if(invertir==original){
        cout<<original<<" Es un numero palindrome"<<endl;
    }
    else{
        cout<<"No es palindrome"<<endl;
}
    return 0;
}
