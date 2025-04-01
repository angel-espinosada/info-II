#include <iostream>

using namespace std;

int main()
{ char a;
    char vocales[5]={'a','e','i','o','u'};
    char consonantes[]={'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

    cout << "Ingrese un letra" << endl;
    cin>>a;
    for (int i=0;i<=26;i++){
        if (vocales[i]=a){
            cout <<"es vocal"<<endl;
        }
}
    return 0;
}
