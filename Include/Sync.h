#ifndef _SYNC_H_
#define _SYNC_H_

#include <mutex>
#include <condition_variable>

#include "Types.h"

class Barrier {
       std::unique_lock<std::mutex> lock;
       std::condition_variable cv;
       std::mutex m;
       uint remaining;
  public:
       /* Constructors */
       Barrier(uint how_many);

       /* Methods */
       void wait(void);

       //~Barrier();
};

#endif
