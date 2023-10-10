import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ServerApp {
    public static void main(String[] args) {
        try {
            // Crea una instancia de la implementación de la tarjeta de crédito
            CreditCard card = new CreditCardImpl();
            
            // Crea el registro RMI en el puerto predeterminado (1099)
            Registry registry = LocateRegistry.createRegistry(1099);
            
            // Vincula la instancia de la tarjeta de crédito al nombre "CreditCardService"
            registry.bind("CreditCardService", card);

            System.out.println("Servidor iniciado correctamente...");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
