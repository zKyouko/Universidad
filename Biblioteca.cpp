#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Clase base Libro
class Libro {
protected:
    std::string id;
    std::string titulo;
    std::string autor;
    int anioPublicacion;
    bool disponible;

public:
    Libro(std::string id, std::string titulo, std::string autor, int anioPublicacion)
        : id(id), titulo(titulo), autor(autor), anioPublicacion(anioPublicacion), disponible(true) {}

    virtual void prestamo() {
        disponible = false;
    }

    virtual void devolucion() {
        disponible = true;
    }

    bool esDisponible() const {
        return disponible;
    }

    virtual std::string toString() const {
        std::stringstream ss;
        ss << "ID: " << id << ", Titulo: " << titulo << ", Autor: " << autor
           << ", Anio: " << anioPublicacion << ", " << (disponible ? "Disponible" : "Prestado");
        return ss.str();
    }

    std::string getId() const {
        return id;
    }

    std::string getTitulo() const {
        return titulo;
    }
};

// Clase derivada LibroFiccion
class LibroFiccion : public Libro {
private:
    std::string genero;

public:
    LibroFiccion(std::string id, std::string titulo, std::string autor, int anioPublicacion, std::string genero)
        : Libro(id, titulo, autor, anioPublicacion), genero(genero) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << Libro::toString() << ", Genero: " << genero;
        return ss.str();
    }
};

// Clase derivada LibroNoFiccion
class LibroNoFiccion : public Libro {
private:
    std::string tema;

public:
    LibroNoFiccion(std::string id, std::string titulo, std::string autor, int anioPublicacion, std::string tema)
        : Libro(id, titulo, autor, anioPublicacion), tema(tema) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << Libro::toString() << ", Tema: " << tema;
        return ss.str();
    }
};

// Clase Usuario
class Usuario {
private:
    std::string id;
    std::string nombre;
    std::string email;
    std::vector<Libro*> prestamosActivos;

public:
    Usuario(std::string id, std::string nombre, std::string email)
        : id(id), nombre(nombre), email(email) {}

    void registrarPrestamo(Libro* libro) {
        prestamosActivos.push_back(libro);
    }

    void registrarDevolucion(Libro* libro) {
        // Buscar y eliminar el libro de la lista de prestamos activos
        for (size_t i = 0; i < prestamosActivos.size(); ++i) {
            if (prestamosActivos[i] == libro) {
                prestamosActivos.erase(prestamosActivos.begin() + i);
                break; // Detenerse despues de eliminar el libro
            }
        }
    }

    std::vector<Libro*> obtenerPrestamosActivos() const {
        return prestamosActivos;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "ID: " << id << ", Nombre: " << nombre << ", Email: " << email;
        return ss.str();
    }

    std::string getId() const {
        return id;
    }

    // Metodo para mostrar los prestamos activos del usuario
    std::string mostrarPrestamosActivos() const {
        std::stringstream ss;
        if (prestamosActivos.empty()) {
            ss << "No tiene prestamos activos.\n";
        } else {
            for (size_t i = 0; i < prestamosActivos.size(); ++i) {
                ss << prestamosActivos[i]->toString() << "\n";
            }
        }
        return ss.str();
    }

    std::string getNombre() const {
        return nombre;
    }
};

// Clase Biblioteca
class Biblioteca {
private:
    std::vector<Libro*> libros;
    std::vector<Usuario*> usuarios;

public:
    Biblioteca() {}

    void agregarLibro(Libro* libro) {
        libros.push_back(libro);
    }

    void agregarUsuario(Usuario* usuario) {
        usuarios.push_back(usuario);
    }

    void prestarLibro(std::string idLibro, std::string idUsuario) {
        Libro* libro = buscarLibro(idLibro);
        Usuario* usuario = buscarUsuario(idUsuario);

        if (libro && usuario && libro->esDisponible()) {
            libro->prestamo();
            usuario->registrarPrestamo(libro);
            std::cout << "Prestamo realizado exitosamente.\n";
        } else {
            std::cout << "No se puede realizar el prestamo. Verifique la disponibilidad del libro o el ID del usuario.\n";
        }
    }

    void devolverLibro(std::string idLibro, std::string idUsuario) {
        Libro* libro = buscarLibro(idLibro);
        Usuario* usuario = buscarUsuario(idUsuario);

        if (libro && usuario) {
            libro->devolucion();
            usuario->registrarDevolucion(libro);
            std::cout << "Devolucion realizada exitosamente.\n";
        } else {
            std::cout << "No se puede realizar la devolucion. Verifique los datos ingresados.\n";
        }
    }

    Libro* buscarLibro(std::string idLibro) const {
        for (size_t i = 0; i < libros.size(); ++i) {
            if (libros[i]->getId() == idLibro) {
                return libros[i];
            }
        }
       // return nullptr;
    }

    Usuario* buscarUsuario(std::string idUsuario) const {
        for (size_t i = 0; i < usuarios.size(); ++i) {
            if (usuarios[i]->getId() == idUsuario) {
                return usuarios[i];
            }
        }
       // return nullptr;
    }

    std::string mostrarLibros() const {
        std::stringstream ss;
        for (size_t i = 0; i < libros.size(); ++i) {
            ss << libros[i]->toString() << "\n";
        }
        return ss.str();
    }

    std::string mostrarUsuarios() const {
        std::stringstream ss;
        for (size_t i = 0; i < usuarios.size(); ++i) {
            ss << usuarios[i]->toString() << "\n";
        }
        return ss.str();
    }

    // Funcion para buscar libros por ID o titulo
    std::string buscarLibroPorIDOTitulo(std::string criterio) const {
        std::stringstream ss;
        bool encontrado = false;
        for (size_t i = 0; i < libros.size(); ++i) {
            if (libros[i]->getId() == criterio || libros[i]->getTitulo() == criterio) {
                ss << libros[i]->toString() << "\n";
                encontrado = true;
            }
        }

        if (!encontrado) {
            ss << "No se encontro ningun libro con el criterio proporcionado.\n";
        }

        return ss.str();
    }

    // Funcion para buscar usuarios por ID o nombre
    std::string buscarUsuarioPorIDONombre(std::string criterio) const {
        std::stringstream ss;
        bool encontrado = false;
        for (size_t i = 0; i < usuarios.size(); ++i) {
            if (usuarios[i]->getId() == criterio || usuarios[i]->getNombre() == criterio) {
                ss << usuarios[i]->toString() << "\n";
                encontrado = true;
            }
        }

        if (!encontrado) {
            ss << "No se encontro ningun usuario con el criterio proporcionado.\n";
        }

        return ss.str();
    }
};

// Funcion para el menu de la interfaz en linea de comandos
void menu() {
    Biblioteca biblioteca;

    // Agregar algunos libros y usuarios de ejemplo
    Libro* libro1 = new LibroFiccion("1", "El Hobbit", "J.R.R. Tolkien", 1937, "Aventura");
    Libro* libro2 = new LibroNoFiccion("2", "Historia del Mundo", "John Doe", 2001, "Historia");
    Usuario* usuario1 = new Usuario("1", "Juan Perez", "juan@gmail.com");
    Usuario* usuario2 = new Usuario("2", "Ana Garcia", "ana@gmail.com");

    biblioteca.agregarLibro(libro1);
    biblioteca.agregarLibro(libro2);
    biblioteca.agregarUsuario(usuario1);
    biblioteca.agregarUsuario(usuario2);

    int opcion;
    do {
        std::cout << "\n--- Menu Biblioteca ---\n";
        std::cout << "1. Mostrar libros\n";
        std::cout << "2. Mostrar usuarios\n";
        std::cout << "3. Prestar libro\n";
        std::cout << "4. Devolver libro\n";
        std::cout << "5. Ver prestamos activos\n";
        std::cout << "6. Agregar nuevo usuario\n";
        std::cout << "7. Agregar nuevo libro\n";
        std::cout << "8. Buscar libro\n";
        std::cout << "9. Buscar usuario\n";
        std::cout << "10. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << biblioteca.mostrarLibros();
                break;
            case 2:
                std::cout << biblioteca.mostrarUsuarios();
                break;
            case 3: {
                std::string idLibro, idUsuario;
                std::cout << "Ingrese ID del libro a prestar: ";
                std::cin >> idLibro;
                std::cout << "Ingrese ID del usuario: ";
                std::cin >> idUsuario;
                biblioteca.prestarLibro(idLibro, idUsuario);
                break;
            }
            case 4: {
                std::string idLibro, idUsuario;
                std::cout << "Ingrese ID del libro a devolver: ";
                std::cin >> idLibro;
                std::cout << "Ingrese ID del usuario: ";
                std::cin >> idUsuario;
                biblioteca.devolverLibro(idLibro, idUsuario);
                break;
            }
            case 5: {
                std::string idUsuario;
                std::cout << "Ingrese ID del usuario para ver sus préstamos activos: ";
                std::cin >> idUsuario;
                Usuario* usuario = biblioteca.buscarUsuario(idUsuario);
                if (usuario) {
                    std::cout << usuario->mostrarPrestamosActivos();
                } else {
                    std::cout << "Usuario no encontrado.\n";
                }
                break;
            }
            case 6: {
                std::string id, nombre, email;
                std::cout << "Ingrese ID del nuevo usuario: ";
                std::cin >> id;
                std::cin.ignore(); // Para limpiar el buffer
                std::cout << "Ingrese nombre del nuevo usuario: ";
                std::getline(std::cin, nombre);
                std::cout << "Ingrese email del nuevo usuario: ";
                std::getline(std::cin, email);
                Usuario* nuevoUsuario = new Usuario(id, nombre, email);
                biblioteca.agregarUsuario(nuevoUsuario);
                std::cout << "Nuevo usuario agregado exitosamente.\n";
                break;
            }
            case 7: { 
                std::string id, titulo, autor, tipo, genero, tema;
                int anioPublicacion;
                
                std::cout << "Ingrese ID del nuevo libro: ";
                std::cin >> id;
                std::cin.ignore(); // Limpiar buffer
                std::cout << "Ingrese título del libro: ";
                std::getline(std::cin, titulo);
                std::cout << "Ingrese autor del libro: ";
                std::getline(std::cin, autor);
                std::cout << "Ingrese año de publicación: ";
                std::cin >> anioPublicacion;
                std::cout << "¿Es un libro de ficción o no ficción? (ficcion/no_ficcion): ";
                std::cin >> tipo;

                if (tipo == "ficcion") {
                    std::cout << "Ingrese género del libro: ";
                    std::cin.ignore();
                    std::getline(std::cin, genero);
                    Libro* nuevoLibro = new LibroFiccion(id, titulo, autor, anioPublicacion, genero);
                    biblioteca.agregarLibro(nuevoLibro);
                    std::cout << "Nuevo libro de ficción agregado exitosamente.\n";
                } else if (tipo == "no_ficcion") {
                    std::cout << "Ingrese tema del libro: ";
                    std::cin.ignore();
                    std::getline(std::cin, tema);
                    Libro* nuevoLibro = new LibroNoFiccion(id, titulo, autor, anioPublicacion, tema);
                    biblioteca.agregarLibro(nuevoLibro);
                    std::cout << "Nuevo libro de no ficción agregado exitosamente.\n";
                } else {
                    std::cout << "Tipo de libro no válido. Intente de nuevo.\n";
                }
                break;
            }
            case 8: {  // Nueva opción para buscar libros
                std::string criterio;
                std::cout << "Ingrese ID o título del libro a buscar: ";
                std::cin.ignore();  // Limpiar buffer
                std::getline(std::cin, criterio);
                std::cout << biblioteca.buscarLibroPorIDOTitulo(criterio);
                break;
            }
            case 9: {  // Nueva opción para buscar usuarios
                std::string criterio;
                std::cout << "Ingrese ID o nombre del usuario a buscar: ";
                std::cin.ignore();  // Limpiar buffer
                std::getline(std::cin, criterio);
                std::cout << biblioteca.buscarUsuarioPorIDONombre(criterio);
                break;
            }
            case 10:
                std::cout << "Gracias por usar la biblioteca. ¡Hasta luego!\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 10);
}

int main() {
    menu();
    return 0;
}


