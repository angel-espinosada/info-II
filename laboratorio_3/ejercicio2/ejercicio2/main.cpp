#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
using namespace std;

// === PROTOTIPOS ===
void ContarBits(const string& binario, int& unos, int& ceros);
string codificarMetodo1Interno(const string& binario, int tamBloque, int& nbloques);
string textoABinario(const string& texto);
void crearClaveAdmin();
bool validarClaveAdmin();

// === FUNCIÓN PRINCIPAL ===
int main() {
    setlocale(LC_ALL, "UTF-8");

    cout << "=== Sistema del Cajero - Acceso Administrador ===\n";
    cout << "1. Crear clave del administrador\n";
    cout << "2. Ingresar como administrador\n";
    cout << "Opcion: ";
    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        crearClaveAdmin();
    } else if (opcion == 2) {
        if (validarClaveAdmin()) {
            cout << "\nMenú de gestión de usuarios (a implementar...)\n";
        }
    } else {
        cout << "Opcion invalida\n";
    }

    return 0;
}

// === DEFINICIONES ===

void ContarBits(const string& binario, int& unos, int& ceros) {
    unos = ceros = 0;
    for (char bit : binario) {
        if (bit == '1') unos++;
        else if (bit == '0') ceros++;
    }
}

string codificarMetodo1Interno(const string& binario, int tamBloque, int& nbloques) {
    nbloques = 0;
    string bloqueAnterior = "";
    string binarioCodificado = "";

    for (int i = 0; i < binario.length(); i += tamBloque) {
        string bloque = binario.substr(i, tamBloque);
        string bloqueOriginal = bloque;
        string bloqueCodificado = "";

        if (i == 0) {
            for (char bit : bloque)
                bloqueCodificado += (bit == '0') ? '1' : '0';
        } else {
            int unos = 0, ceros = 0;
            ContarBits(bloqueAnterior, unos, ceros);

            if (ceros > unos) {
                for (int j = 0; j < bloque.length(); ++j)
                    bloqueCodificado += (j % 2 == 1) ? ((bloque[j] == '0') ? '1' : '0') : bloque[j];
            } else if (unos > ceros) {
                for (int j = 0; j < bloque.length(); ++j)
                    bloqueCodificado += ((j + 1) % 3 == 0) ? ((bloque[j] == '0') ? '1' : '0') : bloque[j];
            } else {
                for (char bit : bloque)
                    bloqueCodificado += (bit == '0') ? '1' : '0';
            }
        }

        binarioCodificado += bloqueCodificado;
        bloqueAnterior = bloqueOriginal;
        nbloques++;
    }

    return binarioCodificado;
}

string textoABinario(const string& texto) {
    string binario = "";
    for (char c : texto)
        binario += bitset<8>(c).to_string();
    return binario;
}

void crearClaveAdmin() {
    string clave;
    cout << "Crea la clave del administrador: ";
    cin >> clave;

    string binClave = textoABinario(clave);

    int bloques = 0;
    string codificada = codificarMetodo1Interno(binClave, 4, bloques);

    ofstream out("sudo.txt");
    if (out.is_open()) {
        out << codificada;
        out.close();
        cout << "Clave del administrador guardada en sudo.txt\n";
    } else {
        cout << "Error al guardar sudo.txt\n";
    }
}

bool validarClaveAdmin() {
    ifstream in("sudo.txt");
    if (!in.is_open()) {
        cout << "No se encontró sudo.txt. Usa crearClaveAdmin() primero.\n";
        return false;
    }

    string claveGuardada;
    getline(in, claveGuardada);
    in.close();

    string clave;
    cout << "\nIngrese la clave del administrador: ";
    cin >> clave;

    string binClave = textoABinario(clave);

    int bloques = 0;
    string codificada = codificarMetodo1Interno(binClave, 4, bloques);

    if (codificada == claveGuardada) {
        cout << "Acceso concedido.\n";
        return true;
    } else {
        cout << "Clave incorrecta.\n";
        return false;
    }
}

