#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0; // Variable compartida entre threads
mutex counterMutex; // Mutex para controlar el acceso a la variable

void increment_counter() {
    cout << "Thread " << this_thread::get_id() << " está comenzando." << endl;

    {
        lock_guard<mutex> guard(counterMutex); // Bloquear el mutex durante la modificación de counter
        cout << "Thread " << this_thread::get_id() << " ha bloqueado el mutex." << endl;
        counter++;
        cout << "Thread " << this_thread::get_id() << " incrementó counter a " << counter << endl;
    } // Mutex se libera automáticamente aquí

    cout << "Thread " << this_thread::get_id() << " ha liberado el mutex." << endl;
    cout << "Thread " << this_thread::get_id() << " está finalizando." << endl;
}

int main() {
    // Crear el primer thread
    thread t1(increment_counter);
    // Crear el segundo thread
    thread t2(increment_counter);

    // Esperar por el primer thread para finalizar
    t1.join();
    // Esperar por el segundo thread para finalizar
    t2.join();

    cout << "Valor final de counter: " << counter << endl;

    return 0;
}

// file_name: shared_counter_mutex.cpp
// exec: g++ -o shared_counter_mutex shared_counter_mutex.cpp -std=c++11 -pthread && ./shared_counter_mutex
