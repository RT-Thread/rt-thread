#ifndef __SDHCI_TIME_H__
#define __SDHCI_TIME_H__

#include <rtthread.h>
#include <sys/time.h>
#include "head.h"
typedef int64_t ktime_t;

#define NSEC_PER_USEC   1000L
#define NSEC_PER_SEC    1000000000L
#define NSEC_PER_MSEC   1000000L
#define ktime_add_ns(kt, nsval)     ((kt) + (nsval))

void usleep_range(unsigned long min, unsigned long max);
unsigned int jiffies_to_msecs(const unsigned long j);
int64_t ktime_add_ms(const ktime_t kt, const rt_uint64_t msec);
int ktime_compare(const ktime_t cmp1, const ktime_t cmp2);
int64_t ktime_get(void);
rt_bool_t ktime_after(const ktime_t cmp1, const ktime_t cmp2);
unsigned long nsecs_to_jiffies(rt_uint64_t n);
int mod_timer(struct rt_timer *timer, unsigned long expires);
#endif