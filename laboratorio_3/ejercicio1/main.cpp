#include <iostream>
#include<fstream>
#include <string>
#include<bitset>

//Crear si no existe	ofstream archivo("archivo.txt");
//Leer (no crea)	ifstream archivo("archivo.txt");
//Leer y escribir	`fstream archivo("archivo.txt", ios::in
using namespace std;

void leerachivo(string& datos);
string ConvertiraBin(const string NombreArchivo);
void MonstrarContenido(const string& NombreArchivo);

int main()
{
    string texto = "ejemplo.txt";
    leerachivo(texto);
    MonstrarContenido(texto);

    return 0;

}
void leerachivo(string &datos){
   fstream archivo(datos);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
    } else {
        cout << "Archivo abierto correctamente." << endl;
    }
}

    string ConvertiraBin(const string NombreArchivo){

        ifstream archivo(NombreArchivo);
        string binario= "";
        char c;

        while (archivo.get (c)) {
            binario+=bitset<8>(c).to_string();

        }

        return binario;

    }

    void MonstrarContenido(const string& NombreArchivo){
        ifstream archivo(NombreArchivo);
        string line;
        if (archivo.is_open()){
            while (getline(archivo,line)){
                cout <<line<<endl;
            }


        }
        else{
            cout <<"No se pudo abrir el archivo"<<NombreArchivo<<endl;
        }

        archivo.close();
    }
