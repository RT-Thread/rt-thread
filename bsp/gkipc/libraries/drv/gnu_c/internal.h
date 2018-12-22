#ifndef  STARTUP_INTERNAL_H
#define STARTUP_INTERNAL_H

#include "gtypes.h"
typedef U8		        uint8_t;
typedef U16		        uint16_t;
typedef U32		        uint32_t;
typedef S32			    int32_t;

typedef char            char_t;
typedef U64             uint64_t;
typedef S64             int64_t;

typedef uint32_t (*enter_crit)(void);

typedef void (*exit_crit)(uint32_t data);


int st_register_crit_func(enter_crit enter, exit_crit exit);

uint32_t st_enter_crit_func();

void st_exit_crit_func(uint32_t flags);

#endif
