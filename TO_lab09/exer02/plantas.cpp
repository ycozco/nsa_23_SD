#include <iostream>
#include <string>
#include <vector>
#include <map>

class Planta {
public:
    virtual Planta* clone() const = 0;
    virtual void mostrar() const = 0;
    virtual ~Planta() {}
};

class PlantaTrepadora : public Planta {
public:
    Planta* clone() const override {
        return new PlantaTrepadora(*this);
    }
    void mostrar() const override {
        std::cout << "Planta Trepadora" << std::endl;
    }
};

class PlantaArbolNormal : public Planta {
public:
    Planta* clone() const override {
        return new PlantaArbolNormal(*this);
    }
    void mostrar() const override {
        std::cout << "Planta Árbol Normal" << std::endl;
    }
};

class PlantaOrnamental : public Planta {
public:
    Planta* clone() const override {
        return new PlantaOrnamental(*this);
    }
    void mostrar() const override {
        std::cout << "Planta Ornamental" << std::endl;
    }
};

class PlantaBonsai : public Planta {
public:
    Planta* clone() const override {
        return new PlantaBonsai(*this);
    }
    void mostrar() const override {
        std::cout << "Planta Bonsái" << std::endl;
    }
};

class Sector {
private:
    std::vector<Planta*> plantas;

public:
    void agregarPlanta(const Planta& planta) {
        plantas.push_back(planta.clone());
    }

    void mostrarPlantas() const {
        for (const auto& planta : plantas) {
            planta->mostrar();
        }
    }

    ~Sector() {
        for (auto& planta : plantas) {
            delete planta;
        }
    }
};

int main() {
    PlantaTrepadora trepadora;
    PlantaArbolNormal arbolNormal;
    PlantaOrnamental ornamental;
    PlantaBonsai bonsai;

    Sector sectorTrepadoras;
    Sector sectorArbolesNormales;

    sectorTrepadoras.agregarPlanta(trepadora);
    sectorTrepadoras.agregarPlanta(ornamental);

    sectorArbolesNormales.agregarPlanta(arbolNormal);
    sectorArbolesNormales.agregarPlanta(bonsai);

    std::cout << "Plantas en el sector de Trepadoras:" << std::endl;
    sectorTrepadoras.mostrarPlantas();

    std::cout << "\nPlantas en el sector de Árboles Normales:" << std::endl;
    sectorArbolesNormales.mostrarPlantas();

    return 0;
}
