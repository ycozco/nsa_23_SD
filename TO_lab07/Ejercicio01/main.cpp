#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Clase base para todos los items de la laptop
class Item {
public:
    virtual string GetName() = 0;
    virtual float GetPrice() = 0;
    virtual void GetConfiguration() = 0;
    virtual ~Item() {}
};

// Clases derivadas para cada componente específico
class Processor : public Item {
protected:
    string name;
    float price;
    string specs;

public:
    Processor(const string& n, float p, const string& s) : name(n), price(p), specs(s) {}

    string GetName() override { return name; }
    float GetPrice() override { return price; }
    void GetConfiguration() override { cout << specs << endl; }
};

class IntelI5 : public Processor {
public:
    IntelI5() : Processor("Intel i5", 3000.0, "2.5 GHz, 6 MB cache, 4 cores") {}
};

class IntelI7 : public Processor {
public:
    IntelI7() : Processor("Intel i7", 4500.0, "3.0 GHz, 8 MB cache, 8 cores") {}
};
// Continúa con la implementación de clases para Disco, Monitor, etc.

// Clase para representar el color de la laptop
class Color : public Item {
    string colorName;
public:
    Color(string name) : colorName(name) {}
    string GetName() override { return colorName; }
    float GetPrice() override { return 20.0; } // Ejemplo de precio por color
    void GetConfiguration() override { cout << "Color: " << colorName << endl; }
};

// Clase para representar la marca de la laptop
class Brand : public Item {
    string brandName;
public:
    Brand(string name) : brandName(name) {}
    string GetName() override { return brandName; }
    float GetPrice() override { return 50.0; } // Ejemplo de precio por marca
    void GetConfiguration() override { cout << "Brand: " << brandName << endl; }
};

// Clase para representar un monitor plasma
class MonitorPlasma : public Item {
    int size;
public:
    MonitorPlasma(int sz) : size(sz) {}
    string GetName() override { return "Monitor Plasma"; }
    float GetPrice() override { return size * 100; } // El precio aumenta con el tamaño
    void GetConfiguration() override { cout << "Monitor Plasma, " << size << " pulgadas" << endl; }
};
// Clase para representar una impresora
class Printer : public Item {
    string type;
public:
    Printer(string t) : type(t) {}
    string GetName() override { return "Printer " + type; }
    float GetPrice() override { return type == "Laser" ? 800.0 : 400.0; }
    void GetConfiguration() override { cout << "Printer Type: " << type << endl; }
};
// Clase Laptop que contiene los componentes
class Laptop {
    vector<Item*> mLaptopParts;
public:
    void AddParts(Item* item) { mLaptopParts.push_back(item); }
    float GetCost() {
        float cost = 0.0;
        for (auto& item : mLaptopParts) {
            cost += item->GetPrice();
        }
        return cost;
    }
    void GetConfiguration() {
        for (auto& item : mLaptopParts) {
            item->GetConfiguration();
        }
    }
    ~Laptop() {
        for (auto& item : mLaptopParts) {
            delete item;
        }
    }
};

// Clase LaptopBuilder que sigue el patrón Builder
class LaptopBuilder {
public:
    Laptop* BuildBasicLaptop() {
        Laptop* laptop = new Laptop();
        laptop->AddParts(new IntelI5());
        // Añadir más partes básicas...
        return laptop;
    }
    Laptop* BuildAdvancedLaptop() {
        Laptop* laptop = new Laptop();
        laptop->AddParts(new IntelI7());
        // Añadir más partes avanzadas...
        return laptop;
    }
    // Métodos para añadir Color, Brand, MonitorPlasma, Printer, etc.
};

int main() {
    LaptopBuilder builder;
    Laptop* myLaptop = builder.BuildBasicLaptop();
    myLaptop->GetConfiguration();
    cout << "Precio: " << myLaptop->GetCost() << endl;
    delete myLaptop; // No olvides liberar la memoria
    return 0;
}
