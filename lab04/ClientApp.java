import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ClientApp {
    public static void main(String[] args) {
        try {
            // Localiza el registro RMI en el host y puerto especificados.
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);

            // Busca el objeto remoto registrado bajo el nombre "CreditCardService".
            CreditCard cardService = (CreditCard) registry.lookup("CreditCardService");

            // Usando el servicio, p.ej. verifica un número de tarjeta de crédito
            boolean isValid = cardService.validateCard("1234-5678-1234-5678");
            System.out.println(isValid ? "Tarjeta válida" : "Tarjeta inválida");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
