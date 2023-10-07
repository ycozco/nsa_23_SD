package com.example;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CalculatorService extends Remote { 
    public int add(int a, int b) throws RemoteException; 
    public int subtract(int a, int b) throws RemoteException; 
}
