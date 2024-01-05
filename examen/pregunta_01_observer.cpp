#include <iostream>
#include <list>
#include <string>

// Observer Interface
class Observer {
public:
    // Función virtual pura para la actualización
    virtual void update(const std::string &message_from_subject) = 0;
};

// Subject Interface
class Subject {
public:
    // Funciones virtuales puras para la gestión de observadores
    virtual void attach(Observer *observer) = 0;
    virtual void detach(Observer *observer) = 0;
    virtual void notify() = 0;
};

// Concrete Subject
class Course : public Subject {
public:
    // Implementación de las funciones de gestión de observadores
    void attach(Observer *observer) override {
        list_observers.push_back(observer);
    }

    void detach(Observer *observer) override {
        list_observers.remove(observer);
    }

    void notify() override {
        for (Observer *observer : list_observers) {
            observer->update(message_);
        }
    }

    // Función para crear un mensaje y notificar a los observadores
    void createMessage(std::string message = "Vacio") {
        this->message_ = message;
        notify();
    }

private:
    // Lista de observadores y mensaje del curso
    std::list<Observer *> list_observers;
    std::string message_;
};

// Concrete Observer
class Student : public Observer {
public:
    // Constructor que establece el nombre del estudiante
    Student(std::string name) : name_(name) {}

    // Implementación de la función de actualización
    void update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        printInfo();
    }

    // Función para imprimir la información del estudiante
    void printInfo() {
        std::cout << "Estudiante " << name_ << " Notificacion recibida: " << message_from_subject_ << std::endl;
    }

private:
    // Nombre del estudiante y mensaje recibido
    std::string name_;
    std::string message_from_subject_;
};

int main() {
    // Crear instancias de Subject (Course) y Observers (Students)
    Course *course = new Course;
    Student *student1 = new Student("Yoset");
    Student *student2 = new Student("Garlet");

    // Registrar estudiantes como observadores
    course->attach(student1);
    course->attach(student2);

    // Crear un mensaje para mandar a los estudiantes
    course->createMessage("Nueva tarea asignada");

    // Liberar recursos
    delete student1;
    delete student2;
    delete course;

    return 0;
}


// file_name: pregunta_01_observer.cpp
// exec: g++ -o pregunta_01_observer pregunta_01_observer.cpp && ./pregunta_01_observer
