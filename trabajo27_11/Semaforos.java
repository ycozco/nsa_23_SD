public class Semaforos {
    public static void main(String[] args) {
        Semaforo semaforo1 = new Semaforo(Semaforo.Estado.ROJO);
        Semaforo semaforo2 = new Semaforo(Semaforo.Estado.ROJO);

        Thread hilo1 = new Thread(() -> gestion(semaforo1));
        Thread hilo2 = new Thread(() -> gestion(semaforo2));

        hilo1.start();
        hilo2.start();
    }

    private static void gestion(Semaforo semaforo) {
        for (int i = 0; i < 10; i++) {
            cambiarEstado(semaforo);
            try {
                Thread.sleep(1000); // Espera 1 segundo antes de cambiar el estado
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private static void cambiarEstado(Semaforo semaforo) {
        switch (semaforo.getEstado()) {
            case ROJO:
                semaforo.setEstado(Semaforo.Estado.VERDE);
                break;
            case AMARILLO:
                semaforo.setEstado(Semaforo.Estado.ROJO);
                break;
            case VERDE:
                semaforo.setEstado(Semaforo.Estado.AMARILLO);
                break;
        }
        System.out.println("Estado del semáforo: " + semaforo.getEstado());
    }

    // Clase interna Semaforo
    static class Semaforo {
        public enum Estado {
            ROJO, AMARILLO, VERDE
        }

        private Estado estadoActual;

        public Semaforo(Estado estadoInicial) {
            this.estadoActual = estadoInicial;
        }

        public void setEstado(Estado nuevoEstado) {
            this.estadoActual = nuevoEstado;
        }

        public Estado getEstado() {
            return estadoActual;
        }
    }
}
