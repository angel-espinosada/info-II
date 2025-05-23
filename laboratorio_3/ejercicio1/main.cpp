#include <iostream>
#include<fstream>
#include <string>
#include<bitset>
#include <clocale>

//Crear si no existe	ofstream archivo("archivo.txt");
//Leer (no crea)	ifstream archivo("archivo.txt");
//Leer y escribir	`fstream archivo("archivo.txt", ios::in
using namespace std;

void leerachivo(string& datos);
string ConvertiraBin(const string NombreArchivo);
void MonstrarContenido(const string& NombreArchivo);
void ContarBits(const string& binario, int& unos, int& ceros );
void DividirBloques(const string& binario, int& nbloques);
string InvertirTodos(const string& bloque);
string InvertirPorPares(const string& bloque);
string InvertirPorTernas(const string& bloque);
string binarioATexto(const string& binario);
void guardarComoTexto(const string& nombreArchivo, const string& binario);
//Funcion segundo metodo

void codificarPorDesplazamiento(const string& binario, int n);

//Funciones para decodificar

string desInvertirTodos(const string& bloque);
string desInvertirPorPares(const string& bloque);
string desInvertirPorTernas(const string& bloque);
void DecodificarMetodo1(const string& binarioCodificado, int n);
//Funcion para leer el binario
string leerBinarioDesdeArchivo(const string& nombreArchivo);

// decodificar segundo metdo
void DecodificarMetodo2(const string& binarioCodificado, int tamBloque);

int main() {
    string archivoEntrada = "ejemplo.txt";
    string archivoSalida  = "salida.bin";
    int tamBloque, metodo, opcion;

    setlocale(LC_ALL, "UTF-8");

    cout << "=== MENU PRINCIPAL ===" << endl;
    cout << "1. Convertir archivo a binario (texto a bin)" << endl;
    cout << "2. Codificar binario" << endl;
    cout << "3. Decodificar archivo binario" << endl;
    cout << "4. Salir" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        string bin = ConvertiraBin(archivoEntrada);
        cout << "Binario generado:\n" << bin << endl;
        ContarBits(bin, tamBloque, metodo);  // temporal uso de vars

    } else if (opcion == 2) {
        cout << "Tamano del bloque: ";
        cin >> tamBloque;
        cout << "Metodo (1 o 2): ";
        cin >> metodo;

        string bin = ConvertiraBin(archivoEntrada);

        if (metodo == 1) {
            DividirBloques(bin, tamBloque);
        } else if (metodo == 2) {
            codificarPorDesplazamiento(bin, tamBloque);
        }

    } else if (opcion == 3) {
        cout << "Tamano del bloque: ";
        cin >> tamBloque;
        cout << "Metodo de decodificacion (1 o 2): ";
        cin >> metodo;

        string binarioCodificado = leerBinarioDesdeArchivo(archivoSalida);

        if (metodo == 1) {
            DecodificarMetodo1(binarioCodificado, tamBloque);
        } else if (metodo == 2) {
            DecodificarMetodo2(binarioCodificado, tamBloque);
        }

    } else {
        cout << "Saliendo..." << endl;
    }

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
        //cout << "Total de unos: " << unos << endl;
        //cout << "Total de ceros: " << ceros << endl;

    }

    // Invertir todos los bits (sin cambiar orden)
    string InvertirTodos(const string& bloque) {
        string resultado = "";
        for (char bit : bloque) {
            resultado += (bit == '0') ? '1' : '0';
        }
        return resultado;
    }

    // Invertir solo los bits en posiciones impares (índice 1, 3, 5...)
    string InvertirPorPares(const string& bloque) {
        string resultado = "";
        for (int i = 0; i < bloque.length(); ++i) {
            if (i % 2 == 1)  // si es el segundo bit del par
                resultado += (bloque[i] == '0') ? '1' : '0';
            else
                resultado += bloque[i];
        }
        return resultado;
    }

    // Invertir solo los bits en posiciones múltiplos de 3 (último bit de cada terna)
    string InvertirPorTernas(const string& bloque) {
        string resultado = "";
        for (int i = 0; i < bloque.length(); ++i) {
            if ((i + 1) % 3 == 0)  // último bit de la terna
                resultado += (bloque[i] == '0') ? '1' : '0';
            else
                resultado += bloque[i];
        }
        return resultado;
    }

    void DividirBloques(const string& binario, int& nbloques) {
        int n = 4;
        nbloques = 0;
        string bloqueAnterior = "";
        string binarioCodificado = "";

        for (int i = 0; i < binario.length(); i += n) {
            string bloque = binario.substr(i, n);
            string bloqueOriginal = bloque;
            string bloqueCodificado = "";

            //cout << "\n=== BLOQUE #" << nbloques + 1 << " ===" << endl;
            //cout << "Bloque original: " << bloque << endl;

            if (i == 0) {
                bloqueCodificado = InvertirTodos(bloque);
                //cout << "Regla: Primer bloque → Invertir todos los bits" << endl;
            } else {
                int unos = 0, ceros = 0;
                ContarBits(bloqueAnterior, unos, ceros);
                //cout << "Bloque anterior: " << bloqueAnterior
                    // << " | Unos: " << unos << " Ceros: " << ceros << endl;

                if (ceros > unos) {
                    bloqueCodificado = InvertirPorPares(bloque);
                   // cout << "Regla: Más ceros → Invertir bits impares (por pares)" << endl;
                } else if (unos > ceros) {
                    bloqueCodificado = InvertirPorTernas(bloque);
                    //cout << "Regla: Más unos → Invertir cada tercer bit (por ternas)" << endl;
                } else {
                    bloqueCodificado = InvertirTodos(bloque);
                    //cout << "Regla: Igual cantidad → Invertir todos los bits" << endl;
                }
            }

            //cout << "Bloque codificado: " << bloqueCodificado << endl;
            binarioCodificado += bloqueCodificado;
            bloqueAnterior = bloqueOriginal;
            nbloques++;
        }

        cout << "\n=== RESULTADO FINAL ===" << endl;
        cout << "Cadena binaria codificada completa: " << binarioCodificado << endl;
        ofstream salida("salida1.bin", ios::binary);
        if (salida.is_open()) {
            salida << binarioCodificado;
            salida.close();
            cout << "Archivo guardado correctamente en salida.bin" << endl;
        } else {
            cout << "No se pudo guardar el archivo." << endl;
        }
    }
//funcion del segundo metodo

    void codificarPorDesplazamiento(const string& binario, int n) {
        string resultado = "";
        cout << "\n=== Codificación por desplazamiento circular ===" << endl;

        for (int i = 0; i < binario.length(); i += n) {
            string bloque = binario.substr(i, n);

            if (bloque.length() < n) {
                // Si el último bloque es incompleto, se ignora o se puede completar con ceros
                cout << "Bloque incompleto ignorado: " << bloque << endl;
                continue;
            }

            string codificado = bloque.back() + bloque.substr(0, n - 1);
            resultado += codificado;

            //cout << "Bloque original: " << bloque
                // << " → Codificado: " << codificado << endl;
        }

        cout << "\n=== Resultado final codificado ===" << endl;
        cout << resultado << endl;
        ofstream salida("salida.bin", ios::binary);
        if (salida.is_open()) {
            salida << resultado;
            salida.close();
            cout << "Archivo guardado correctamente en salida.bin" << endl;
        } else {
            cout << "No se pudo guardar el archivo." << endl;
        }
    }


    //Funciones para decodificar

    string desInvertirTodos(const string& bloque) {
        string resultado = "";
        for (char bit : bloque) {
            resultado += (bit == '0') ? '1' : '0';
        }
        return resultado;
    }


    string desInvertirPorPares(const string& bloque) {
        string resultado = "";
        for (int i = 0; i < bloque.length(); ++i) {
            if (i % 2 == 1)  // si es el segundo bit del par
                resultado += (bloque[i] == '0') ? '1' : '0';
            else
                resultado += bloque[i];  // dejar el primero igual
        }
        return resultado;
    }



    string desInvertirPorTernas(const string& bloque) {
        string resultado = "";
        for (int i = 0; i < bloque.length(); ++i) {
            // Invertimos solo el tercer bit de cada grupo de 3
            if ((i + 1) % 3 == 0)
                resultado += (bloque[i] == '0') ? '1' : '0';
            else
                resultado += bloque[i];
        }
        return resultado;
    }




    void DecodificarMetodo1(const string& binarioCodificado, int n) {
        string resultado = "";
        string bloqueAnterior = "";  // debe ser el anterior YA DECODIFICADO
        int nbloques = 0;

        cout << "\n=== DECODIFICACIÓN - MÉTODO 1 ===\n";

        for (int i = 0; i < binarioCodificado.length(); i += n) {
            string bloque = binarioCodificado.substr(i, n);
            string bloqueDecodificado = "";

            cout << "\n--- Bloque #" << nbloques + 1 << " ---" << endl;
            cout << "Bloque codificado: " << bloque << endl;

            if (nbloques == 0) {
                bloqueDecodificado = desInvertirTodos(bloque);
                cout << "Regla: primer bloque → invertir todos los bits" << endl;
            } else {
                int unos = 0, ceros = 0;
                for (char bit : bloqueAnterior) {
                    if (bit == '1') unos++;
                    else if (bit == '0') ceros++;
                }

                cout << "Bloque anterior decodificado: " << bloqueAnterior << " | Unos: " << unos << " Ceros: " << ceros << endl;

                if (ceros > unos) {
                    bloqueDecodificado = desInvertirPorPares(bloque);
                    cout << "Regla: más ceros → desinvertir por pares" << endl;
                } else if (unos > ceros) {
                    bloqueDecodificado = desInvertirPorTernas(bloque);
                    cout << "Regla: más unos → desinvertir por ternas" << endl;
                } else {
                    bloqueDecodificado = desInvertirTodos(bloque);
                    cout << "Regla: igual cantidad → desinvertir todos" << endl;
                }
            }

            cout << "Bloque decodificado: " << bloqueDecodificado << endl;

            resultado += bloqueDecodificado;

            // ✅ Guardamos el bloque ya decodificado (muy importante)
            bloqueAnterior = bloqueDecodificado;
            nbloques++;
        }

        cout << "\n=== BINARIO RECUPERADO ===" << endl;
        cout << resultado << endl;
        guardarComoTexto("salida_decodificada1.txt", resultado);
    }


    string leerBinarioDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo, ios::binary);
        string contenido;

        if (archivo.is_open()) {
            // Leemos todo el contenido en un solo string
            string linea;
            while (getline(archivo, linea)) {
                contenido += linea;
            }
            archivo.close();
            cout << "Archivo binario leído: " << nombreArchivo << endl;
            cout << "Contenido del archivo binario:\n" << contenido << endl;
        } else {
            cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        }

        return contenido;
    }

    string binarioATexto(const string& binario) {
        string texto = "";

        for (int i = 0; i + 7 < binario.length(); i += 8) {
            string byte = binario.substr(i, 8);
            char caracter = static_cast<char>(bitset<8>(byte).to_ulong());
            texto += caracter;
        }

        return texto;
    }
    void guardarComoTexto(const string& nombreArchivo, const string& binario) {
        string texto = binarioATexto(binario);
        ofstream salida(nombreArchivo);

        if (salida.is_open()) {
            salida << texto;
            salida.close();
            cout << "✅ Texto recuperado guardado en: " << nombreArchivo << endl;
        } else {
            cout << "❌ No se pudo guardar el archivo de texto." << endl;
        }
    }

//decodificar segundo metodo

    // Rotar bits a la izquierda (decodificación del método 2)
    string rotarIzquierda(const string& bloque) {
        if (bloque.empty()) return "";
        return bloque.substr(1) + bloque[0];
    }

    // Decodificación método 2: desplazamiento circular inverso
    void DecodificarMetodo2(const string& binarioCodificado, int tamBloque) {
        cout << "\n=== DECODIFICACIÓN - MÉTODO 2 ===\n" << endl;

        string binarioDecodificado = "";

        for (int i = 0; i < binarioCodificado.length(); i += tamBloque) {
            string bloque = binarioCodificado.substr(i, tamBloque);
            string decodificado = rotarIzquierda(bloque);

            cout << "Bloque original codificado: " << bloque << " → Decodificado: " << decodificado << endl;

            binarioDecodificado += decodificado;
        }

        cout << "\n=== BINARIO RECUPERADO ===\n" << binarioDecodificado << endl;

        // Convertir binario a texto y guardar
        guardarComoTexto("salida_decodificada2.txt", binarioDecodificado);
    }

/*

    void DividirBloques(const string& binario, int& nbloques) {
        int n = 4;                          // Tamaño del bloque (como dice el taller)
        nbloques = 0;                      // Contador de bloques
        string bloqueAnterior = "";       // Guarda el bloque anterior original
        string binarioCodificado = "";    // Resultado final de todos los bloques codificados

        // Recorre el binario de n en n (de 4 en 4)
        for (int i = 0; i < binario.length(); i += n) {
            string bloque = binario.substr(i, n);  // Extrae un bloque de 4 bits
            string bloqueOriginal = bloque;        // Guarda el original sin codificar
            string bloqueCodificado = "";          // Acumulador del bloque ya codificado

            if (i == 0) {
                // 🔹 Primer bloque → se invierte totalmente (regla fija)
                for (char bit : bloque) {
                    bloqueCodificado += (bit == '0') ? '1' : '0';  // Cambia cada bit
                }
                cout << "Primer bloque codificado: " << bloqueCodificado << endl;

            } else {
                // 🔍 Se cuentan los bits del bloque anterior original
                int unos = 0, ceros = 0;
                ContarBits(bloqueAnterior, unos, ceros);

                if (unos == ceros) {
                    // 🔹 Si hay igual número → invertir todos los bits
                    for (char bit : bloque) {
                        bloqueCodificado += (bit == '0') ? '1' : '0';
                    }

                } else if (ceros > unos) {
                    // 🔸 Si hay más ceros → invertir el orden de cada 2 bits
                    for (int j = 0; j < bloque.length(); j += 2) {
                        if (j + 1 < bloque.length()) {
                            bloqueCodificado += bloque[j + 1];  // Segundo bit primero
                            bloqueCodificado += bloque[j];      // Primer bit segundo
                        } else {
                            bloqueCodificado += bloque[j];      // Si queda uno suelto, se queda igual
                        }
                    }

                } else {
                    // 🔺 Si hay más unos → invertir el orden de cada 3 bits
                    for (int j = 0; j < bloque.length(); j += 3) {
                        if (j + 2 < bloque.length()) {
                            bloqueCodificado += bloque[j + 2];  // Tercer bit
                            bloqueCodificado += bloque[j + 1];  // Segundo bit
                            bloqueCodificado += bloque[j];      // Primero
                        } else {
                            // Si quedan 1 o 2 bits sueltos, se copian tal como están
                            for (int k = j; k < bloque.length(); ++k) {
                                bloqueCodificado += bloque[k];
                            }
                        }
                    }
                }

                // 🖨️ Muestra el bloque codificado (a partir del segundo)
                cout << "Bloque " << nbloques << " codificado: " << bloqueCodificado << endl;
            }

            // 🧱 Acumula el bloque codificado en la cadena final
            binarioCodificado += bloqueCodificado;

            // 🔁 Guarda el original como referencia para el siguiente
            bloqueAnterior = bloqueOriginal;

            // 🔢 Aumenta el contador de bloques
            nbloques++;
        }

        // 📦 Imprime el resultado final
        cout << "Cadena binaria codificada completa: " << binarioCodificado << endl;
    }



    void DividirBloques(const string& binario, int& nbloques) {
        int n = 4;                          // Tamaño de cada bloque
        nbloques = 0;                       // Contador de bloques
        string bloqueAnterior = "";        // Guarda el bloque anterior original
        string binarioCodificado = "";     // Acumulador del resultado final

        for (int i = 0; i < binario.length(); i += n) {
            string bloque = binario.substr(i, n);
            string bloqueOriginal = bloque;
            string bloqueCodificado = "";

            cout << "\n=== BLOQUE #" << nbloques + 1 << " ===" << endl;
            cout << "Bloque original: " << bloqueOriginal << endl;

            if (i == 0) {
                // Primer bloque → invertir todos los bits
                for (char bit : bloque) {
                    bloqueCodificado += (bit == '0') ? '1' : '0';
                }
                cout << "Regla: Primer bloque → Invertir todos los bits" << endl;
            } else {
                // Contar bits del bloque anterior (sin codificar)
                int unos = 0, ceros = 0;
                ContarBits(bloqueAnterior, unos, ceros);
                cout << "Bloque anterior: " << bloqueAnterior << " | Unos: " << unos << " Ceros: " << ceros << endl;

                if (unos == ceros) {
                    cout << "Regla: Unos == Ceros → Invertir todos los bits" << endl;
                    for (char bit : bloque) {
                        bloqueCodificado += (bit == '0') ? '1' : '0';
                    }

                } else if (ceros > unos) {
                    cout << "Regla: Más ceros → Invertir el orden de cada 2 bits" << endl;
                    // Versión segura para bloques de tamaño fijo = 4
                    for (int j = 0; j < bloque.length(); j += 2) {
                        if (j + 1 < bloque.length()) {
                            bloqueCodificado += bloque[j + 1];
                            bloqueCodificado += bloque[j];
                        } else {
                            bloqueCodificado += bloque[j];
                        }
                    }

                } else {
                    cout << "Regla: Más unos → Invertir el orden de cada 3 bits" << endl;
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
            }

            cout << "Bloque codificado: " << bloqueCodificado << endl;

            // Acumular resultado
            binarioCodificado += bloqueCodificado;
            bloqueAnterior = bloqueOriginal;
            nbloques++;
        }

        cout << "\n=== RESULTADO FINAL ===" << endl;
        cout << "Cadena binaria codificada completa: " << binarioCodificado << endl;
    }
*/
