#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>

using namespace std;
class Anfitrion {
private:
    string numeroDocumento;
    string nombre;
    int antiguedadMeses;
    float puntuacion;
    string* alojamientos;
    int cantidadAlojamientos;

public:
    // Constructor por defecto
    Anfitrion();

    // Constructor con parámetros
    Anfitrion(string doc, string nombre, int antiguedad, float punt);

    // Constructor de copia
    Anfitrion(const Anfitrion& otro);

    // Destructor
    ~Anfitrion();

    // Operador de asignación
    Anfitrion& operator=(const Anfitrion& otro);

    // Getters
    string getNumeroDocumento();
    string getNombre();
    int getAntiguedad();
    float getPuntuacion();
    int getCantidadAlojamientos();
    string getAlojamiento(int i);

    // Setters
    void setNombre(string nuevoNombre);
    void setAntiguedad(int meses);
    void setPuntuacion(float nuevaPuntuacion);
    void setAlojamientos(string* lista, int cantidad);
    void medirConsumoRecursos();

    // Utilidad
    void mostrarInfo();

    // Convierte el objeto a texto para guardar en archivo
    string toTexto() const;

    // Método estático para cargar anfitriones desde archivo
    static Anfitrion* cargarDesdeArchivo(const string& nombreArchivo, int& cantidad);

};
#endif // ANFITRION_H
