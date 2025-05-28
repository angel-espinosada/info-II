#include <iostream>

using namespace std;

int main()
<<<<<<< HEAD
{   bool conso =false;
    char a;
=======
{ char a, i;
    bool vocal=false;
>>>>>>> 587b03cc78cab4ad99390e4655060f3a806b0007
    char vocales[5]={'a','e','i','o','u'};
    char consonantes[]={'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

    cout << "Ingrese un letra" << endl;
    cin>>a;
    for (int i=0;i<=5;i++){
        if (vocales[i]==a){
<<<<<<< HEAD
            conso=true;
        //cout <<"es vocal"<<a<<vocales[i]<<i<<endl;
=======
            vocal=true;
            break;
>>>>>>> 587b03cc78cab4ad99390e4655060f3a806b0007
        }


}
<<<<<<< HEAD
    if(  conso=true){
cout <<"Es cpnso"<<endl;
    }
    if (  conso=false){
        cout<<"es vocal"<<endl;
=======
    if(vocal){
    cout <<"Es vocal"<<endl;}
    else{
        cout <<"No es vocal"<<endl;
>>>>>>> 587b03cc78cab4ad99390e4655060f3a806b0007
    }
    return 0;
}
