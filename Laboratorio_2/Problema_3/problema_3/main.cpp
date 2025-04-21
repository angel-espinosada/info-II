#include <iostream>
#include <cstring>
using namespace std;

int main()


{
    char cadena1[100], cadena2[100];
    int tamano1,tamano2;
    cout << "Comparar longitud de cadenas" << endl;
    cout<<"Ingrese la primera cadena: "<<endl;
    cin.getline(cadena1,100);
    cout<<"Ingrese la segunda  cadena: "<<endl;
    cin.getline(cadena2,100);

    tamano1=strlen(cadena1);
    tamano2=strlen(cadena2);

    if(tamano1!=tamano2){

        cout<<" Las cadenas no son iguales"<<endl;
    }
    else{
        bool igual=true;

        for (int i = 0; i < cadena1[i]!='\0'; ++i) {
            if (cadena1[i] != cadena2[i]) {
                igual = false;
                break;
        }
    }
        if (igual){
        cout<<"las cadenas son iguales"<<endl;

        }
        else{
            cout<<"Las cadenas tiene el mismo tamaño, pero no son iguales"<<endl;
        }
    return 0;
    }}
