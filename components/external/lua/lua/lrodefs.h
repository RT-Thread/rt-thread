/* Read-only tables helper */

#ifndef lrodefs_h
#define lrodefs_h

#include "lrotable.h"

#undef LUA_REG_TYPE
#undef LSTRKEY
#undef LNILKEY
#undef LNUMKEY
#undef LFUNCVAL
#undef LNUMVAL
#undef LROVAL
#undef LNILVAL
#undef LREGISTER

#if (MIN_OPT_LEVEL > 0) && (LUA_OPTIMIZE_MEMORY >= MIN_OPT_LEVEL)
#define LUA_REG_TYPE                luaR_entry 
#define LSTRKEY                     LRO_STRKEY
#define LNUMKEY                     LRO_NUMKEY
#define LNILKEY                     LRO_NILKEY
#define LFUNCVAL                    LRO_FUNCVAL
#define LNUMVAL                     LRO_NUMVAL
#define LROVAL                      LRO_ROVAL
#define LNILVAL                     LRO_NILVAL
#define LREGISTER(L, name, table)\
  return 0
#else
#define LUA_REG_TYPE                luaL_reg
#define LSTRKEY(x)                  x
#define LNILKEY                     NULL
#define LFUNCVAL(x)                 x
#define LNILVAL                     NULL
#define LREGISTER(L, name, table)\
  luaL_register(L, name, table);\
  return 1
#endif

#endif /* lrodefs_h */

