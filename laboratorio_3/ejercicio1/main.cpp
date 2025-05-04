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
void ContarBits(const string& binario, int& unos, int& ceros );
void DividirBloques(const string& binario, int& nbloques);

int main()
{
    string texto = "ejemplo.txt";
    leerachivo(texto);
    MonstrarContenido(texto);
    ConvertiraBin(texto);
    int unos, ceros;
    string bin = ConvertiraBin(texto);
    ContarBits(bin,unos,ceros);

    int cantidadBloques;

    DividirBloques(bin,cantidadBloques);

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
        cout<<binario<<endl;
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
    void ContarBits(const string& binario, int& unos, int& ceros ){
        unos=ceros=0;
        for (char bit:binario) {
            if(bit=='1') unos++;
            else if(bit=='0')ceros++;

        }
        cout << "Total de unos: " << unos << endl;
        cout << "Total de ceros: " << ceros << endl;

    }
    void DividirBloques(const string& binario, int& nbloques) {
        int n = 4;
        nbloques = 0;
        string bloqueAnterior = ""; // el anterior SIN codificar
        string binarioCodificado = "";

        for (int i = 0; i < binario.length(); i += n) {
            string bloque = binario.substr(i, n);         // bloque actual
            string bloqueOriginal = bloque;               // guardar copia original
            string bloqueCodificado = "";

            if (i == 0) {
                // Primer bloque: invertir todos los bits
                for (char bit : bloque) {
                    bloqueCodificado += (bit == '0') ? '1' : '0';
                }
                cout << "Primer bloque codificado: " << bloqueCodificado << endl;
            } else {
                // Contar unos y ceros del bloqueAnterior original
                int unos = 0, ceros = 0;
                ContarBits(bloqueAnterior, unos, ceros);

                if (unos == ceros) {
                    // Invertir todos los bits
                    for (char bit : bloque) {
                        bloqueCodificado += (bit == '0') ? '1' : '0';
                    }
                } else if (ceros > unos) {
                    // Invertir cada 2 bits
                    for (int j = 0; j < bloque.length(); j += 2) {
                        if (j + 1 < bloque.length()) {
                            bloqueCodificado += bloque[j + 1];
                            bloqueCodificado += bloque[j];
                        } else {
                            bloqueCodificado += bloque[j];
                        }
                    }
                } else {
                    // Invertir cada 3 bits
                    for (int j = 0; j < bloque.length(); j += 3) {
                        if (j + 2 < bloque.length()) {
                            bloqueCodificado += bloque[j + 2];
                            bloqueCodificado += bloque[j + 1];
                            bloqueCodificado += bloque[j];
                        } else {
                            for (int k = j; k < bloque.length(); ++k) {
                                bloqueCodificado += bloque[k];
                            }
                        }
                    }
                }

                cout << "Bloque " << nbloques << " codificado: " << bloqueCodificado << endl;
            }

            binarioCodificado += bloqueCodificado;
            bloqueAnterior = bloqueOriginal; // muy importante: guardar el original, no el codificado
            nbloques++;
        }

        cout << "Cadena binaria codificada completa: " << binarioCodificado << endl;
    }
