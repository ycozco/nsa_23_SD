package com.example;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class CalculatorServiceImpl extends UnicastRemoteObject implements CalculatorService { 

    public CalculatorServiceImpl() throws RemoteException { 
        super(); 
    } 

    public int add(int a, int b) throws RemoteException { 
        return a + b; 
    } 

    public int subtract(int a, int b) throws RemoteException { 
        return a - b; 
    } 
}
