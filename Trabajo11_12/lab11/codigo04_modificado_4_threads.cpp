// file_name: codigo04_modificado_4_threads.cpp

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <chrono>
#include <atomic>
using namespace std::chrono_literals;

struct Resource {
    bool full = false;
    std::mutex mux;
    std::condition_variable cond;

    void produce() {
        {
            std::unique_lock<std::mutex> lock(mux);
            cond.wait(lock, [this]{ return !full; });
            std::cout << "Llenando el recurso y notificando al consumidor.\n";
            full = true;
            std::this_thread::sleep_for(200ms);
        }
        cond.notify_one();
    }

    void consume() {
        {
            std::unique_lock<std::mutex> lock(mux);
            cond.wait(lock, [this]{ return full; });
            std::cout << "Consumiendo el recurso y notificando al productor.\n";
            full = false;
            std::this_thread::sleep_for(200ms);
        }
        cond.notify_one();
    }
};

int main() {
    Resource resource;
    std::atomic<bool> running{true};

    // Ajuste para incluir 4 threads adicionales (total de 6 threads)
    std::thread producers[3];
    std::thread consumers[3];

    for (int i = 0; i < 3; ++i) {
        producers[i] = std::thread([&resource, &running](){
            while (running) {
                resource.produce();
            }
        });

        consumers[i] = std::thread([&resource, &running](){
            while (running) {
                resource.consume();
            }
        });
    }

    std::this_thread::sleep_for(2s);
    running = false;

    for (auto& producer : producers) {
        producer.join();
    }

    for (auto& consumer : consumers) {
        consumer.join();
    }

    return 0;
}

// exec: g++ -o codigo04_modificado_4_threads codigo04_modificado_4_threads.cpp -std=c++2a -pthread && ./codigo04_modificado_4_threads
