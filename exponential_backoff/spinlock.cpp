#include "atomic"
#include <immintrin.h>
#include <math.h>

#define MIN_BACKOFF 2
#define MAX_BACKOFF 1024

class spinlock {
    
private:
    std::atomic<unsigned int> _flag;

public:
    spinlock() : _flag(0) {};

    void lock(){
        int iter = MIN_BACKOFF;
        while ( _flag.exchange(1)) {
            // exponential backoff
            // We can also use random time backoff also
            // issue : fairness 
            for(int i = 0; i < iter; i++) _mm_pause();
            iter = std::min(iter << 1, MAX_BACKOFF);
        }
    }

    void unlock(){
        _flag.store(0);
    }
};


