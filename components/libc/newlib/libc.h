#ifndef __RTT_LIBC_H__
#define __RTT_LIBC_H__

void libc_system_init(const char* tty_name);
int libc_time_to_tick(const struct timespec *time);

#endif
