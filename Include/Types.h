#ifndef _TYPES_H_
#define _TYPES_H_

#include <utility>

typedef unsigned int uint;
typedef std::pair<uint, uint> Interval;
typedef union {
    struct {
        uint first;
        uint second;
    };
    bool result;
} Query;

#endif
