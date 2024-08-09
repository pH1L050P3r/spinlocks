#include "atomic"
#include <time.h>


class spinlock {
    
private:
    std::atomic<unsigned int> _currnt;

    // don't need to be atomic
    // dont put this in register so volatile
    volatile unsigned int _serving;

public:
    spinlock() : _currnt(0), _serving(0) {};


    void lock(){
        const struct timespec ns = {0, 1};
        // get ticket
        int ticker = _currnt.fetch_add(1);
        // wait till ticket comes
        uint8_t i = 0;
        while ( ticker != _serving) {
            // Don't get extra time slice to burn
            // Extra trik for fairness
            if(i == 8) {
                i = 0;
                //empirically better to use nanosleep
                nanosleep(&ns, NULL);
            }
            i++;
        }
    }

    void unlock(){
        _serving = _serving + 1;
    }
};


