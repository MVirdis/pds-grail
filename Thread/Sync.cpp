#include <iostream>

#include "Sync.h"

using namespace std;

// Barrier
Barrier::Barrier(uint how_many) {
    this->remaining = how_many;
}

void Barrier::wait(void) {
    unique_lock<mutex> lock(m);
    --remaining;
    if (remaining > 0) {
        while (remaining > 0) {
            cv.wait(lock);
        }
        lock.unlock();
    } else {
        lock.unlock();
        cv.notify_all();
    }
}
