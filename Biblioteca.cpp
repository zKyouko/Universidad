/*     
	Alejandro Mendiola Gonzalez
	Programacion orientada a objetos
	D20
	Prof. MIGUEL ANGEL GUERRERO SEGURA RAMIREZ
     */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Libro; 
class Usuario {
private:
    string id;
    string nombre;
    string email;
    vector<Libro*> prestamosActivos; 

public:

    Usuario(string id, string nombre, string email);
    
    void registrarPrestamo(Libro* libro);
    void registrarDevolucion(Libro* libro);
    vector<Libro*> obtenerPrestamosActivos() const;
    string toString() const;
};

Usuario::Usuario(string id, string nombre, string email)
    : id(id), nombre(nombre), email(email) {}

class Libro {
private:
    string id;
    string titulo; 
    string autor; 
    int anioPublicacion;
    bool disponible;

public:

    Libro(string id, string titulo, string autor, int anioPublicacion);

    void prestamo();
    void devolucion();
    bool esDisponible() const;
    string toString() const;
};

Libro::Libro(string id, string titulo, string autor, int anioPublicacion)
    : id(id), titulo(titulo), autor(autor), anioPublicacion(anioPublicacion), disponible(true) {}

int main() {
    return 0;
}


