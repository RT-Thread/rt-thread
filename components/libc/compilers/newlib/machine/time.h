#ifndef _MACHTIME_H_
#define _MACHTIME_H_

#include <rtconfig.h>
#define _CLOCKS_PER_SEC_   RT_TICK_PER_SECOND

#ifdef __SPU__
#include <sys/_timespec.h>
int nanosleep (const struct timespec *, struct timespec *);
#endif

#endif  /* _MACHTIME_H_ */
