// Lua EGC (Emergeny Garbage Collector) interface

#ifndef __LEGC_H__
#define __LEGC_H__

#include "lstate.h"

// EGC operations modes
#define EGC_NOT_ACTIVE        0   // EGC disabled
#define EGC_ON_ALLOC_FAILURE  1   // run EGC on allocation failure
#define EGC_ON_MEM_LIMIT      2   // run EGC when an upper memory limit is hit
#define EGC_ALWAYS            4   // always run EGC before an allocation

void legc_set_mode(lua_State *L, int mode, unsigned limit);

#endif

