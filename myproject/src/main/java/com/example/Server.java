package com.example;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server { 

    public static void main(String[] args) throws Exception { 
        CalculatorService calculatorService = new CalculatorServiceImpl(); 

        Registry registry = LocateRegistry.createRegistry(1099); 
        registry.bind("CalculatorService", calculatorService); 

        System.out.println("Server started"); 
    } 
}
