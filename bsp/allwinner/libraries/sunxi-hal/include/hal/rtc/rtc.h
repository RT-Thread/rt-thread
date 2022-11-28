#ifndef _RTC_H_
#define _RTC_H_

#include <stdlib.h>
#include <sunxi_hal_common.h>
/*
 * The struct used to pass data via the following ioctl. Similar to the
 * struct tm in <time.h>, but it needs to be here so that the kernel
 * source is self contained, allowing cross-compiles, etc. etc.
 */

struct rtc_time
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

typedef s64 time64_t;
/*
 * This data structure is inspired by the EFI (v0.92) wakeup
 * alarm API.
 */
struct rtc_wkalrm
{
    unsigned char enabled;  /* 0 = alarm disabled, 1 = alarm enabled */
    unsigned char pending;  /* 0 = alarm not pending, 1 = alarm pending */
    struct rtc_time time;   /* time the alarm is set to */
};

typedef enum
{
    RTC_IRQ_ERROR = -3,
    RTC_CLK_ERROR = -2,
    RTC_ERROR = -1,
    RTC_OK = 0,
}hal_rtc_status_t;

int rtc_month_days(unsigned int month, unsigned int year);
int rtc_year_days(unsigned int day, unsigned int month, unsigned int year);
int rtc_valid_tm(struct rtc_time *tm);
time64_t rtc_tm_to_time64(struct rtc_time *tm);
void rtc_time64_to_tm(time64_t time, struct rtc_time *tm);

/*
 * rtc_tm_sub - Return the difference in seconds.
 */
static inline time64_t rtc_tm_sub(struct rtc_time *lhs, struct rtc_time *rhs)
{
    return rtc_tm_to_time64(lhs) - rtc_tm_to_time64(rhs);
}

static inline int is_leap_year(unsigned int year)
{
    return (!(year % 4) && (year % 100)) || !(year % 400);
}


/**
 * Deprecated. Use rtc_time64_to_tm().
 */
static inline void rtc_time_to_tm(unsigned long time, struct rtc_time *tm)
{
    rtc_time64_to_tm(time, tm);
}

/**
 * Deprecated. Use rtc_tm_to_time64().
 */
static inline int rtc_tm_to_time(struct rtc_time *tm, unsigned long *time)
{
    *time = rtc_tm_to_time64(tm);

    return 0;
}
#endif /* _UAPI_LINUX_RTC_H_ */
