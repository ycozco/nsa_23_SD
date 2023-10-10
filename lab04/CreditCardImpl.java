import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class CreditCardImpl extends UnicastRemoteObject implements CreditCard {
    private double balance;

    public CreditCardImpl() throws RemoteException {
        this.balance = 0.0;
    }

    @Override
    public double getBalance() throws RemoteException {
        return balance;
    }

    @Override
    public void charge(double amount) throws RemoteException {
        this.balance += amount;
    }
    public boolean validateCard(String cardNumber) {
        return isValidLuhn(cardNumber);
    }
    private boolean isValidLuhn(String cardNumber) {
        // Remueve guiones de la cadena
        cardNumber = cardNumber.replace("-", "");
        
        int nDigits = cardNumber.length();
        int sum = 0;
        boolean alternate = false;
    
        for (int i = nDigits - 1; i >= 0; i--) {
            int n = Integer.parseInt(cardNumber.substring(i, i + 1));
            
            if (alternate) {
                n *= 2;
                
                if (n > 9) {
                    n -= 9;
                }
            }
    
            sum += n;
            alternate = !alternate;
        }
    
        return (sum % 10 == 0);
    }
    
}
