#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

// === PROTOTIPOS ===
void ContarBits(const string& binario, int& unos, int& ceros);
string codificarMetodo1Interno(const string& binario, int tamBloque, int& nbloques);
string textoABinario(const string& texto);
void crearClaveAdmin();
bool validarClaveAdmin();
void registrarUsuario();

bool accesoUsuario();
string decodificarMetodo1Interno(const string& binarioCod, int tamBloque);
void guardarUsuarios(const vector<string>& lineas);


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
            cout << "\n1. Registrar nuevo usuario\n";
            cout << "2. Ingresar como usuario\n";
            cout << "Opción: ";
            int subop;
            cin >> subop;

            if (subop == 1)
            registrarUsuario();
            else if (subop == 2)
                accesoUsuario();
            else
                cout << "Opción no válida.\n";
        }
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
void registrarUsuario() {
    string cedula, clave;
    int saldo;

    cout << "\n=== Registro de nuevo usuario ===\n";
    cout << "Cédula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> clave;
    cout << "Saldo inicial (COP): ";
    cin >> saldo;

    // Convertir clave a binario
    string binClave = textoABinario(clave);

    // Codificar con método 1 (bloques de 4)
    int bloques = 0;
    string claveCodificada = codificarMetodo1Interno(binClave, 4, bloques);

    // Guardar en usuarios.txt
    ofstream out("usuarios.txt", ios::app); // Agrega sin borrar lo anterior
    if (out.is_open()) {
        out << cedula << "," << claveCodificada << "," << saldo << endl;
        out.close();
        cout << "Usuario registrado correctamente.\n";
    } else {
        cout << "Error al escribir en usuarios.txt\n";
    }
}
string binarioATexto(const string& binario) {
    string texto = "";
    for (size_t i = 0; i < binario.length(); i += 8) {
        string byte = binario.substr(i, 8);
        char c = static_cast<char>(bitset<8>(byte).to_ulong());
        texto += c;
    }
    return texto;
}


string desInvertirPorPares(const string& bloque) {
    string resultado = "";
    for (int i = 0; i < bloque.length(); ++i) {
        if (i % 2 == 1)  // solo impares
            resultado += (bloque[i] == '0') ? '1' : '0';
        else
            resultado += bloque[i];
    }
    return resultado;
}

string desInvertirPorTernas(const string& bloque) {
    string resultado = "";
    for (int i = 0; i < bloque.length(); ++i) {
        if ((i + 1) % 3 == 0)
            resultado += (bloque[i] == '0') ? '1' : '0';
        else
            resultado += bloque[i];
    }
    return resultado;
}

string decodificarMetodo1Interno(const string& binarioCod, int tamBloque) {
    string bloqueAnterior = "";
    string binarioDecodificado = "";

    for (int i = 0; i < binarioCod.length(); i += tamBloque) {
        string bloque = binarioCod.substr(i, tamBloque);
        string bloqueDecod = "";

        if (i == 0) {
            for (char bit : bloque)
                bloqueDecod += (bit == '0') ? '1' : '0';
        } else {
            int unos = 0, ceros = 0;
            ContarBits(bloqueAnterior, unos, ceros);

            if (ceros > unos)
                bloqueDecod = desInvertirPorPares(bloque);
            else if (unos > ceros)
                bloqueDecod = desInvertirPorTernas(bloque);
            else {
                for (char bit : bloque)
                    bloqueDecod += (bit == '0') ? '1' : '0';
            }
        }

        binarioDecodificado += bloqueDecod;
        bloqueAnterior = bloqueDecod;
    }

    return binarioDecodificado;
}
bool accesoUsuario() {
    string cedulaIngresada, claveIngresada;
    cout << "\n=== Ingreso como usuario ===\n";
    cout << "Cédula: ";
    cin >> cedulaIngresada;
    cout << "Clave: ";
    cin >> claveIngresada;

    ifstream in("usuarios.txt");
    if (!in.is_open()) {
        cout << "❌ No se pudo abrir usuarios.txt\n";
        return false;
    }

    string linea;
    vector<string> usuarios;
    bool encontrado = false;

    while (getline(in, linea)) {
        usuarios.push_back(linea);
        size_t p1 = linea.find(',');
        size_t p2 = linea.rfind(',');

        string cedula = linea.substr(0, p1);
        string claveCod = linea.substr(p1 + 1, p2 - p1 - 1);
        int saldo = stoi(linea.substr(p2 + 1));

        if (cedula == cedulaIngresada) {
            string claveDecod = binarioATexto(decodificarMetodo1Interno(claveCod, 4));

            if (claveDecod == claveIngresada) {
                cout << "✅ Acceso concedido\n";

                int opcion;
                cout << "1. Consultar saldo\n2. Retirar dinero\nOpción: ";
                cin >> opcion;

                saldo -= 1000; // cobra acceso

                if (opcion == 1) {
                    cout << "Saldo actual: " << saldo << " COP\n";
                } else if (opcion == 2) {
                    int retiro;
                    cout << "¿Cuánto desea retirar?: ";
                    cin >> retiro;

                    if (retiro + 1000 <= saldo) {
                        saldo -= retiro;
                        cout << "Retiro exitoso. Nuevo saldo: " << saldo << " COP\n";
                    } else {
                        cout << "Fondos insuficientes.\n";
                    }
                }

                // actualizar línea
                usuarios.back() = cedula + "," + claveCod + "," + to_string(saldo);
                encontrado = true;
            } else {
                cout << " Clave incorrecta.\n";
            }
            break;
        }
    }

    in.close();

    if (encontrado) {
        guardarUsuarios(usuarios);
    }

    return encontrado;
}
void guardarUsuarios(const vector<string>& lineas) {
    ofstream out("usuarios.txt");
    for (string l : lineas)
        out << l << endl;
}
