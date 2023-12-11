// file_name: codigo08_modificado_sleep_until.cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>
#include <chrono>

int main() {
    std::condition_variable cond;
    std::mutex mtx;
    std::queue<int> intq;
    bool stopped = false;

    std::thread producer{[&]() {
        std::default_random_engine gen;
        std::uniform_int_distribution<int> dist(0, 100); // Rango de números aleatorios

        std::size_t count = 4006;
        while (count--) {
            std::lock_guard<std::mutex> L{mtx};
            intq.push(dist(gen));
            cond.notify_one();
        }

        std::lock_guard<std::mutex> L{mtx};
        std::cout << "Productor esta hecho!" << std::endl;
        stopped = true;
        cond.notify_one();
    }};

    std::thread consumer{[&]() {
        do {
            std::unique_lock<std::mutex> L{mtx};

            // Modificación aquí: uso de sleep_until
            auto now = std::chrono::system_clock::now();
            cond.wait_until(L, now + std::chrono::milliseconds(100), [&]() {
                return stopped || !intq.empty();
            });

            while (!intq.empty()) {
                const auto val = intq.front();
                intq.pop();
                std::cout << "Consumidor saca: " << val << std::endl;
            }

            if (stopped) {
                std::cout << "Consumidor esta hecho!" << std::endl;
                break;
            }

        } while (true);
    }};

    consumer.join();
    producer.join();
    std::cout << "¡Ejemplo completo!" << std::endl;

    return 0;
}

// exec: g++ -o codigo08_modificado_sleep_until codigo08_modificado_sleep_until.cpp -std=c++17 -pthread && ./codigo08_modificado_sleep_until
