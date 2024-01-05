#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include <random>

// Flyweight Book
class Book {
private:
    std::string title;
    std::string author;

public:
    // Constructor para inicializar un libro con título y autor
    Book(const std::string& title, const std::string& author) : title(title), author(author) {}

    // Método para mostrar la información del libro con un estado dado
    void displayBookInfo(const std::string& status) const {
        std::cout << "Book: " << title << ", Author: " << author << ", Status: " << status << std::endl;
    }
};

// Flyweight Factory
class BookFactory {
private:
    std::unordered_map<std::string, Book*> books;
    std::mutex mutex_;

public:
    // Destructor que libera la memoria de los libros creados
    ~BookFactory() {
        for (auto& pair : books) {
            delete pair.second;
        }
    }

    // Obtiene un libro existente o crea uno nuevo si no existe
    Book* getBook(const std::string& title) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = books.find(title);
        if (it != books.end()) {
            return it->second;
        }

        // Aquí se puede agregar lógica para obtener más detalles del libro si es necesario
        Book* book = new Book(title, "Autor desconocido");
        books[title] = book;
        return book;
    }
};

// Función de simulación del usuario
void userSimulation(BookFactory& factory, int userId, std::mt19937& gen) {
    std::uniform_int_distribution<> dis(1, 100); // Corregir el rango de generación
    for (int i = 0; i < 15; ++i) {
        // Genera un título de libro aleatorio
        std::string bookTitle = "Book" + std::to_string(dis(gen));
        // Obtiene un libro de la fábrica (puede ser nuevo o existente)
        Book* book = factory.getBook(bookTitle);
        // Muestra información sobre el libro en stock
        book->displayBookInfo("en stock");
    }
}

int main() {
    std::cout << "Simulación de Búsqueda de Libros Digitales" << std::endl;

    BookFactory factory;
    std::mt19937 gen(std::random_device{}()); // Generador de números aleatorios

    for (int users = 2000; users <= 12000; users += 2000) {
        std::cout << "Simulando con " << users << " usuarios..." << std::endl;
        std::vector<std::thread> userThreads;

        for (int i = 0; i < users; ++i) {
            userThreads.push_back(std::thread(userSimulation, std::ref(factory), i, std::ref(gen)));
        }

        for (auto& t : userThreads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    return 0;
}

// file_name: pregunta_02_patron_flyweigth.cpp
// exec: g++ -o pregunta_02_patron_flyweigth pregunta_02_patron_flyweigth.cpp -lpthread && ./pregunta_02_patron_flyweigth
