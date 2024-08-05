#include "atomic"


class spinlock {
    
private:
    std::atomic<unsigned int> _flag;

public:
    spinlock() : _flag(0) {};

    void lock(){
        while (_flag.load() || _flag.exchange(1)) {}
    }

    void unlock(){
        _flag.store(0);
    }
};