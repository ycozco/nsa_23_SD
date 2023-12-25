#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

// Espacio de nombres para evitar prefijar con std::
using namespace std;

// Clase base para las partes del automóvil
class Item {
public:
    virtual ~Item() = default;
    virtual string Info() const = 0; // Método virtual puro para obtener información del ítem
};

// Componentes básicos del automóvil como clases
class Door : public Item {
    string color;
public:
    // Constructor que recibe el color de la puerta
    Door(const string& color) : color(color) {
        cout << "Puerta de color " << color << " creada." << endl;
    }
    // Implementación del método Info() para obtener información de la puerta
    string Info() const override {
        return "Puerta de color: " + color;
    }
};

class Engine : public Item {
    string type;
public:
    // Constructor que recibe el tipo de motor
    Engine(const string& type) : type(type) {
        cout << "Motor de tipo " << type << " creado." << endl;
    }
    // Implementación del método Info() para obtener información del motor
    string Info() const override {
        return "Tipo de motor: " + type;
    }
};

class Wheel : public Item {
    string material;
    int size;
public:
    // Constructor que recibe el material y el tamaño de la rueda
    Wheel(const string& material, int size) : material(material), size(size) {
        cout << "Rueda de material " << material << " y tamaño " << size << " creada." << endl;
    }
    // Implementación del método Info() para obtener información de la rueda
    string Info() const override {
        return "Material de la rueda: " + material + ", tamaño: " + to_string(size);
    }
};

class Seat : public Item {
    string material;
    string color;
public:
    // Constructor que recibe el material y el color del asiento
    Seat(const string& material, const string& color) : material(material), color(color) {
        cout << "Asiento de material " << material << " y color " << color << " creado." << endl;
    }
    // Implementación del método Info() para obtener información del asiento
    string Info() const override {
        return "Material del asiento: " + material + ", color: " + color;
    }
};

// Clase para representar el automóvil completo
class Car {
    vector<unique_ptr<Item>> parts;
public:
    // Agrega una parte (puerta, motor, rueda o asiento) al automóvil
    void AddPart(unique_ptr<Item> part) {
        cout << "Parte agregada: " << part->Info() << endl;
        parts.push_back(move(part));
    }

    // Muestra la configuración completa del automóvil
    void ShowConfiguration() const {
        cout << "Configuración del automóvil:" << endl;
        for (const auto& part : parts) {
            cout << part->Info() << endl;
        }
    }
};

// Interfaz Builder
class ICarBuilder {
public:
    // Métodos abstractos para construir las partes del automóvil
    virtual void BuildDoor(const string& color) = 0;
    virtual void BuildEngine(const string& type) = 0;
    virtual void BuildWheel(const string& material, int size) = 0;
    virtual void BuildSeat(const string& material, const string& color) = 0;
    // Método para obtener el automóvil construido
    virtual unique_ptr<Car> GetCar() = 0;
    virtual ~ICarBuilder() {}
};

// Implementación concreta del Builder con C++11
class CarBuilder : public ICarBuilder {
    unique_ptr<Car> car;
public:
    // Constructor que inicializa el automóvil
    CarBuilder() : car(new Car()) {} // Usando C++11 para inicializar el automóvil

    // Implementación de los métodos para construir las partes del automóvil
    void BuildDoor(const string& color) override {
        car->AddPart(unique_ptr<Door>(new Door(color))); // Crear y agregar una puerta
    }
    void BuildEngine(const string& type) override {
        car->AddPart(unique_ptr<Engine>(new Engine(type))); // Crear y agregar un motor
    }
    void BuildWheel(const string& material, int size) override {
        car->AddPart(unique_ptr<Wheel>(new Wheel(material, size))); // Crear y agregar una rueda
    }
    void BuildSeat(const string& material, const string& color) override {
        car->AddPart(unique_ptr<Seat>(new Seat(material, color))); // Crear y agregar un asiento
    }

    // Método para obtener el automóvil construido
    unique_ptr<Car> GetCar() override {
        return move(car);
    }
};

// Director que usa el Builder para crear el automóvil
class CarDirector {
public:
    // Construye un automóvil con las partes especificadas en el mapa de características
    unique_ptr<Car> ConstructCar(ICarBuilder& builder, const map<string, string>& features) {
        cout << "Construyendo automóvil con las siguientes características:" << endl;
        if (features.count("engineType")) {
            builder.BuildEngine(features.at("engineType"));
        }
        if (features.count("doorColor")) {
            builder.BuildDoor(features.at("doorColor"));
        }
        if (features.count("wheelSize")){
            int wheelSize = stoi(features.at("wheelSize"));
            string wheelMaterial = features.at("wheelMaterial");
            builder.BuildWheel(wheelMaterial, wheelSize);
        }
        // Aquí se agregarían más características y componentes según las features...
        return builder.GetCar();
    }
};

// Función para demostrar el uso del patrón Builder
void BuildCarDemo() {
    CarBuilder builder;
    CarDirector director;

    // Características deseadas del coche
    map<string, string> features = {
        {"engineType", "V8"},
        {"doorColor", "rojo"},
        {"wheelMaterial", "aleación"},
        {"wheelSize", "20"},
        {"seatMaterial", "cuero"},
        {"seatColor", "negro"}
    };

    // Construye el automóvil con las características especificadas
    unique_ptr<Car> car = director.ConstructCar(builder, features);
    car->ShowConfiguration(); // Muestra la configuración del automóvil
}

int main() {
    BuildCarDemo(); // Ejecuta la demostración de construcción de automóvil
    return 0;
}

// file_name : exer03.cpp
// exec: g++ -o exer exer03.cpp -std=c++11 && ./exer