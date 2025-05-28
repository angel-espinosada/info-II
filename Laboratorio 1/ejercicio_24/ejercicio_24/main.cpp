#include <iostream>

using namespace std;

int main()
{ int N;
    cout <<"Dibujar patrones" << endl;
    cout << "Ingresa un numero par: "<<endl;
    cin >>N;
    cout << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(i == 0 || i == N - 1 || j == 0 || j == N - 1){
                cout << "+";
            }
            else {
                cout << " ";
            }


        }
         cout << endl;  // Salto de línea al final de cada fila
    }

    return 0;
}
