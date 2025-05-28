#include <iostream>

using namespace std;

int main()
{ int A,B;
    cout << "Clacular el mcm" << endl;
    cout <<"Ingrese el numero A: "<<endl;
            cin>>A;
    cout <<"Ingrese el numero B: "<<endl;
            cin>>B;
    int mult=A;
    int mult1=B;
    while(mult!=mult1){
        if(mult<mult1){
            mult +=A;
        }


            else{
            mult1 +=B;
                }

    }
    cout<<"el mcm es "<<mult<<endl;
    return 0;
}
