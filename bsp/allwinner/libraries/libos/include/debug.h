#ifndef DEBUG_H__
#define DEBUG_H__

#include "arch.h"

#define software_break(...)  \
    do {                     \
        arch_break();        \
    } while(0)

#endif
