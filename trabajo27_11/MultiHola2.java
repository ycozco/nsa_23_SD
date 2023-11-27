class TestTh extends Thread {
    private String nombre;
    private int retardo;

    public TestTh(String s, int d) {
        nombre = s;
        retardo = d;
    }

    public void run() {
        try {
            sleep(retardo);
        } catch (InterruptedException e) {
            // Manejar excepción
        }
        System.out.println("Hola Mundo! " + nombre + " " + retardo);
    }
}

public class MultiHola2 {
    public static void main(String args[]) {
        TestTh[] threads = new TestTh[7];

        // Inicializar los threads en el arreglo
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new TestTh("Thread " + (i + 1), (int) (Math.random() * 2000));
        }

        // Arrancar los threads
        for (TestTh t : threads) {
            t.start();
        }
    }
}
