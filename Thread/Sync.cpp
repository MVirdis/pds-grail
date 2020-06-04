#include "Sync.h"

using namespace std;

// Barrier
Barrier::Barrier(uint how_many) : lock(unique_lock<mutex>(m, defer_lock)) {
    this->remaining = how_many;
}

void Barrier::wait(void) {
    lock.lock();
    --remaining;
    if (remaining > 0) {
        while (remaining > 0)
            cv.wait(this->lock);
    } else {
        cv.notify_all();
    }
    lock.unlock();
}
