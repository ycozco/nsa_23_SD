@Service
public class CalculatorServiceClient { 

	@Autowired
	private CalculatorService calculatorService; 

	public int add(int a, int b) throws RemoteException { 
		return calculatorService.add(a, b); 
	} 

	public int subtract(int a, int b) throws RemoteException { 
		return calculatorService.subtract(a, b); 
	} 

} 
