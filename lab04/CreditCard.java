import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CreditCard extends Remote {
    double getBalance() throws RemoteException;
    void charge(double amount) throws RemoteException;
    boolean validateCard(String cardNumber) throws RemoteException;
}
