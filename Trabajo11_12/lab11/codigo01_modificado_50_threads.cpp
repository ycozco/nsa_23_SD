// file_name: codigo01_modificado_50_threads.cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) cv.wait(lck);
    std::cout << "thread " << id << '\n';
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    std::thread threads[50]; // Modificado para 50 threads
    for (int i = 0; i < 50; ++i) // Modificado para 50 threads
        threads[i] = std::thread(print_id, i);

    std::cout << "50 threads listos para la carrera...\n";
    go();

    for (auto& th : threads) th.join();
    return 0;
}

// exec: g++ -o codigo01_modificado_50_threads codigo01_modificado_50_threads.cpp -std=c++17 -pthread && ./codigo01_modificado_50_threads
