#include <iostream>
#include<cstdlib>//para poder generar las letras
#include<ctime>//para poder que cambie cada que se ejecute
using namespace std;

int main()
{
    int letras=200;
    char letras1[letras];
    cout << "Arreglo de 200 letras mayusculas" << endl;
    int contador[26] = {0};
    srand(time(0));

    for (int i = 0; i <letras; ++i) {
        letras1[i]='A'+rand()%26;
        cout<<letras1[i];
        contador[letras1[i]-'A']++;
        //cout<<contador[i]<<endl;
    }
    cout<<endl;
    for (int i = 0; i <26; ++i) {
        if(contador[i]>0){
            //int pos=letras1[i]-'A';
            char letra='A'+i;
            cout<<letra<<":"<<contador[i]<<endl;
        }

    }
    return 0;
}
