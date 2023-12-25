#include "Receta.cpp"

class FabricaRecetas {
public:
    static Receta* crearReceta(int tipo) {
        Receta* receta = nullptr;

        switch (tipo) {
            case 1:
                receta = new RecetaPasta("Pasta Alfredo", 8.99);
                break;
            case 2:
                receta = new RecetaSopa("Sopa de pollo", 5.99);
                break;
            case 3:
                receta = new RecetaEnsalada("Ensalada César", 7.99);
                break;
            case 4:
                receta = new RecetaPostre("Cheesecake", 6.50);
                break;
            case 5:
                receta = new RecetaAperitivo("Tapas", 4.50);
                break;
            default:
                std::cout << "Tipo de receta no válido, por favor ingrese otra opción" << std::endl;
                return nullptr;
        }

        // 
        receta->preparar();
        receta->cocinar();
        receta->servir();
        receta->mostrarReceta();

        return receta;
    }
};

// file_name: FabricaRecetas.cpp
