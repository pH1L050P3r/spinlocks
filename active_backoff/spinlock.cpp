#include "atomic"


class spinlock {
    
private:
    std::atomic<unsigned int> _flag;

public:
    spinlock() : _flag(0) {};

    void lock(){
        while ( _flag.exchange(1)) {
            // If lock is not free the wait/pause for some time for next check;
            // but processor will execute extra instruction
            for(volatile int i = 0; i < 50000; i++);
        }
    }

    void unlock(){
        _flag.store(0);
    }
};


