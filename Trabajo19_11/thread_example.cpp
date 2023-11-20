#include <iostream>
#include <thread>

class MyThreadFunctions {
public:
    void foo(int id) {
        std::cout << "Thread " << id << " está en foo\n";
    }

    void bar(int id) {
        std::cout << "Thread " << id << " está en bar\n";
    }
};

int main() {
    MyThreadFunctions myObj; // Creación de un objeto de la clase MyThreadFunctions

    // Creación de cuatro threads, dos para cada función
    std::thread th1(&MyThreadFunctions::foo, &myObj, 1);
    std::thread th2(&MyThreadFunctions::foo, &myObj, 2);
    std::thread th3(&MyThreadFunctions::bar, &myObj, 3);
    std::thread th4(&MyThreadFunctions::bar, &myObj, 4);

    // Esperando a que los threads terminen
    th1.join();
    th2.join();
    th3.join();
    th4.join();

    return 0;
}

// file_name: thread_example.cpp
// exec: g++ -o thread_example thread_example.cpp -std=c++11 -pthread && ./thread_example
