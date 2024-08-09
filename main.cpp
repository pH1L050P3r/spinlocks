#include "iostream"
#include "fairness/spinlock.cpp"
#include "thread"
#include "vector"

void run(spinlock &s, unsigned int &val){
    for(int i = 0; i < 1000; i++){
        s.lock();
        val++;
        s.unlock();
    }
}

int main(){
    const int NUM_OF_THREADS = 32;
    unsigned int count = 0;

    std::vector<std::thread> threads;
    spinlock s;

    std::cout << "Value before execution : " << count << std::endl;

    for(int i = 0; i < NUM_OF_THREADS; i++){
        threads.emplace_back([&] { run(s, count);});
    }

    for(int i = 0; i < NUM_OF_THREADS; i++){
        threads[i].join();
    }

    std::cout << "Value Afer execution : " << count << std::endl;
    
    return 0;
}