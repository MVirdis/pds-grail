#include "Thread.h"

// Barrier
Barrier::Barrier(uint how_many) {
    pthread_barrier_init(&(this->tbarrier), NULL, how_many);
}

Barrier::~Barrier() {
    pthread_barrier_destroy(&(this->tbarrier));
}

Barrier& Barrier::wait(void) {
    pthread_barrier_wait(&(this->tbarrier));
    return *this;
}

// Mutex
Mutex::Mutex() {
    pthread_mutex_init(&(this->tmutex), NULL);
}

Mutex& Mutex::lock(void) {
    pthread_mutex_lock(&(this->tmutex));
    return *this;
}

Mutex& Mutex::unlock(void) {
    pthread_mutex_unlock(&(this->tmutex));
    return *this;
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&(this->tmutex));
}
