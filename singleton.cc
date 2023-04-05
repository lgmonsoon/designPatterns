#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <algorithm>

class Singleton {
public:
    static std::atomic<int> i;
    static Singleton& getInstance() {
        static Singleton instance;
        i++;
        return instance;
    }
    
private:
    Singleton() { static int i = 0; std::cout << "Singleton " << i++ << std::endl; };
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
std::atomic<int> Singleton::i = 0;

int main() {
    std::vector<std::thread> thrds;
    for(int i = 0; i < 100000; i++) {
        thrds.emplace_back(std::thread([](){auto& a = Singleton::getInstance();}));
    }
    for_each(thrds.begin(), thrds.end(), [](auto& t){ t.join(); });
    std::cout << "i = " << Singleton::i << std::endl;
}
