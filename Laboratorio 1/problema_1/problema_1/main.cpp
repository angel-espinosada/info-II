#include <iostream>

using namespace std;

int main()
{   bool conso =false;
    char a;
    char vocales[5]={'a','e','i','o','u'};
    char consonantes[]={'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

    cout << "Ingrese un letra" << endl;
    cin>>a;
    for (int i=0;i<=25;i++){
        if (vocales[i]==a){
            conso=true;
        //cout <<"es vocal"<<a<<vocales[i]<<i<<endl;
        }


}
    if(  conso=true){
cout <<"Es cpnso"<<endl;
    }
    if (  conso=false){
        cout<<"es vocal"<<endl;
    }
    return 0;
}
