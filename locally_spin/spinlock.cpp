#include "atomic"


class spinlock {
    
private:
    std::atomic<unsigned int> _flag;

public:
    spinlock() : _flag(0) {};

    void lock(){
        // dont write again and again to lock variable that is causing coherent miss
        // first read the lock value if lock if free then try to aquire lock
        while (_flag.load() ||  _flag.exchange(1)) {}
    }

    void unlock(){
        _flag.store(0);
    }
};


