#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

// Función utilitaria para la creación de un thread
void sleepThread() {
    cout << "Thread iniciando el sueño." << endl;
    this_thread::sleep_for(chrono::minutes(1));
    cout << "Thread despertando después de 1 minuto." << endl;
}

int main() {
    // Creando thread1 y thread2
    thread thread1(sleepThread);
    thread thread2(sleepThread);

    thread::id t1_id = thread1.get_id();
    thread::id t2_id = thread2.get_id();

    cout << "ID asociado con thread1 = " << t1_id << endl;
    cout << "ID asociado con thread2 = " << t2_id << endl;

    thread1.join();
    thread2.join();

    return 0;
}

// file_name: sleep_thread_example.cpp
// exec: g++ -o sleep_thread_example sleep_thread_example.cpp -std=c++11 -pthread && ./sleep_thread_example
