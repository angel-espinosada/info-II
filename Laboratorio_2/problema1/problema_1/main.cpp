#include <iostream>

using namespace std;

int main()
{int N,  C, V,D,CM,DM, M,Q,DC,CN,CT ;
    cout << "Programa que determina cantidad e billetes y monedas" << endl;
    cout <<"Ingrese el valor: "<<endl;
    cin>>N;
    cout<<endl;
    C=N/50000;
    int restoV=N%50000;
    V=restoV/20000;
    int restoD=restoV%20000;
    D=restoD/10000;
    int restoCM=restoD%10000;
    CM=restoCM/5000;
    int restoDM=restoCM%5000;
    DM= restoDM/2000;
    int restoM=restoDM%2000;
    M=restoM/1000;
    int restoQ=restoM%1000;
    Q=restoQ/500;
    int restoDC=restoQ%500;
    DC=restoDC/200;
    int restoCN=restoDC%200;
    CN=restoCN/100;
    int restoCT=restoCN%100;
    CT=restoCT/50;
    int restoF=restoCT%50;


    cout<<"50000: "<<C<<endl;
    cout<<"20000: "<<V<<endl;
    cout<<"10000: "<<D<<endl;
    cout<<"5000: "<<CM<<endl;
    cout<<"2000: "<<DM<<endl;
    cout<<"1000: "<<M<<endl;
    cout<<"500: "<<Q<<endl;
    cout<<"200: "<<DC<<endl;
    cout<<"100: "<<CN<<endl;
    cout<<"50: "<<CT<<endl;
    cout<<"Faltante : "<<restoF<<endl;



    return 0;
}
