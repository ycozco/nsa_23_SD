#include <iostream>
#include <string>

class Receta {
protected:
    std::string nombre;
    float precio;

public:
    Receta(const std::string& nom, float prec) : nombre(nom), precio(prec) {}

    virtual void preparar() = 0;
    virtual void cocinar() = 0;
    virtual void servir() = 0;

    void mostrarReceta() {
        std::cout << "Receta: " << nombre << " - Precio: " << precio << " USD" << std::endl;
    }

    virtual ~Receta() {}
};

class RecetaPasta : public Receta {
public:
    RecetaPasta(const std::string& nom, float prec) : Receta(nom, prec) {}

    void preparar() override {
        std::cout << "Preparando ingredientes para la pasta." << std::endl;
    }

    void cocinar() override {
        std::cout << "Cocinando la pasta." << std::endl;
    }

    void servir() override {
        std::cout << "Sirviendo la pasta." << std::endl;
    }
};

class RecetaSopa : public Receta {
public:
    RecetaSopa(const std::string& nom, float prec) : Receta(nom, prec) {}

    void preparar() override {
        std::cout << "Preparando ingredientes para la sopa." << std::endl;
    }

    void cocinar() override {
        std::cout << "Cocinando la sopa." << std::endl;
    }

    void servir() override {
        std::cout << "Sirviendo la sopa." << std::endl;
    }
};

class RecetaEnsalada : public Receta {
public:
    RecetaEnsalada(const std::string& nom, float prec) : Receta(nom, prec) {}

    void preparar() override {
        std::cout << "Preparando ingredientes para la ensalada." << std::endl;
    }

    void cocinar() override {
        std::cout << "Cocinando la ensalada." << std::endl;
    }

    void servir() override {
        std::cout << "Sirviendo la ensalada." << std::endl;
    }
};

class RecetaPostre : public Receta {
public:
    RecetaPostre(const std::string& nom, float prec) : Receta(nom, prec) {}

    void preparar() override {
        std::cout << "Preparando ingredientes para el postre." << std::endl;
    }

    void cocinar() override {
        std::cout << "Cocinando el postre." << std::endl;
    }

    void servir() override {
        std::cout << "Sirviendo el postre." << std::endl;
    }
};

class RecetaAperitivo : public Receta {
public:
    RecetaAperitivo(const std::string& nom, float prec) : Receta(nom, prec) {}

    void preparar() override {
        std::cout << "Preparando ingredientes para el aperitivo." << std::endl;
    }

    void cocinar() override {
        std::cout << "Cocinando el aperitivo." << std::endl;
    }

    void servir() override {
        std::cout << "Sirviendo el aperitivo." << std::endl;
    }
};
