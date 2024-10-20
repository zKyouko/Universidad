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

Usuario::Usuario(string id, string nombre, string email) : id(id), nombre(nombre), email(email) {}

class UsuarioEstudiante : public Usuario{
	private:
		string numeroMatricula;
	public:
		UsuarioEstudiante(string id, string nombre, string email, string numeroMatricula );
};

	UsuarioEstudiante::UsuarioEstudiante(string _id, string _nombre, string _email,string _numeroMatricula ) : Usuario(_id, _nombre, _email){
	numeroMatricula = _numeroMatricula;
	}

	
class UsuarioProfesor : public Usuario{
	private:
		string departamento;
	public:
		UsuarioProfesor(string id, string nombre, string email, string departamento  );
};

	UsuarioProfesor::UsuarioProfesor(string _id, string _nombre, string _email,string _departamento ) : Usuario(_id, _nombre, _email){
	departamento  = _departamento;
	}
	
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

class LibroFiccion : public Libro{
	private:
		string genero;
	public: 
		LibroFiccion (string id, string titulo, string autor, int anioPublicacion, string genero);
};

LibroFiccion :: LibroFiccion (string _id, string _titulo, string _autor, int _anioPublicacion, string _genero) : Libro(_id, _titulo, _autor, _anioPublicacion){
	genero= _genero;
}

class LibroNoFiccion : public Libro{
	private:
		string tema ;
	public: 
		LibroNoFiccion (string id, string titulo, string autor, int anioPublicacion, string _tema );
};

LibroNoFiccion :: LibroNoFiccion (string _id, string _titulo, string _autor, int _anioPublicacion, string _tema ) : Libro(_id, _titulo, _autor, _anioPublicacion){
	tema  = _tema;
}

Libro::Libro(string id, string titulo, string autor, int anioPublicacion)
    : id(id), titulo(titulo), autor(autor), anioPublicacion(anioPublicacion), disponible(true) {}
    
class biblioteca {
private:
    vector<Libro*> libros;
    vector<Usuario*> usuarios;

public:
    Biblioteca();
    void agregarLibro(Libro* libro);
    void agregarUsuario(Usuario* usuario);
    void prestarLibro(string idLibro, string idUsuario);
    void devolverLibro(string idLibro, string idUsuario);
    Libro* buscarLibro(string idLibro) const;
    Usuario* buscarUsuario(string idUsuario) const;
    string mostrarLibros() const;
    string mostrarUsuarios() const;
};

int main() {
    return 0;
}


