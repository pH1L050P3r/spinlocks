#include "atomic"
#include <immintrin.h>

class spinlock {
    
private:
    std::atomic<unsigned int> _flag;

public:
    spinlock() : _flag(0) {};

    void lock(){
        while ( _flag.exchange(1)) {
            for(volatile int i = 0; i < 4; i++){
                // The execution of the next instruction is delayed for an implementation-specific amount of time. 
                // The PAUSE instruction does not modify the architectural state. For dynamic scheduling, the PAUSE instruction reduces the penalty of exiting from the spin-loop. 
                // It also reduce power consumption
                _mm_pause();
            };
        }
    }

    void unlock(){
        _flag.store(0);
    }
};


