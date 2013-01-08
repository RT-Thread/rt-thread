#ifndef __RTT_LIBC_H__
#define __RTT_LIBC_H__

#include <sys/time.h>

#define MILLISECOND_PER_SECOND	1000UL
#define MICROSECOND_PER_SECOND	1000000UL
#define NANOSECOND_PER_SECOND	1000000000UL

#define MILLISECOND_PER_TICK	(MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK	(MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK		(NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)

void libc_system_init(const char* tty_name);

/* some time related function */
int libc_set_time(const struct timespec *time);
int libc_get_time(struct timespec *time);
int libc_time_to_tick(const struct timespec *time);

#endif
