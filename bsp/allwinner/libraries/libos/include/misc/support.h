/*
 * =====================================================================================
 *
 *       Filename:  support.h
 *
 *    Description:  misc utilities definition.
 *
 *        Version:  2.0
 *         Create:  2017-11-03 11:34:34
 *       Revision:  none
 *       Compiler:  gcc version 6.3.0 (crosstool-NG crosstool-ng-1.23.0)
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2020-03-25 12:20:13
 *
 * =====================================================================================
 */

#ifndef __SUPPORT_H__
#define __SUPPORT_H__
#include <typedef.h>
#include <kapi.h>
/*
 * Generic macro to convert pointers to values for comparison purposes.
 */
#ifndef p2n
#define p2n(p)      ((ptrdiff_t)((ptrdiff_t*)(p)))
#endif

/*
 * min()/max() macros that also do
 * strict type-checking.. See the
 * "unnecessary" pointer comparison.
 */
#ifndef min
#define min(x,y) ({ \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        (void) (&_x == &_y);        \
        _x < _y ? _x : _y; })
#endif

#ifndef max
#define max(x,y) ({ \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        (void) (&_x == &_y);        \
        _x > _y ? _x : _y; })
#endif

/*
 * ..and if you can't take the strict
 * types, you can specify one yourself.
 *
 * Or not use min/max at all, of course.
 */
#define min_t(type,x,y) \
    ({ type __x = (x); type __y = (y); __x < __y ? __x: __y; })
#define max_t(type,x,y) \
    ({ type __x = (x); type __y = (y); __x > __y ? __x: __y; })


//#define BITS_PER_LONG 32
//#define BITS_PER_LONG_LONG 64

#ifndef ALIGN
#define ALIGN(val,align)    (((val) + ((align) - 1)) & ~((align) - 1))
#endif
#define LONG_ALIGN(x) (((x)+(sizeof(long))-1)&~((sizeof(long))-1))
#ifndef INT_MAX
#define INT_MAX     ((int)(~0U>>1))
#endif
#ifndef INT_MIN
#define INT_MIN     (-INT_MAX - 1)
#endif
#ifndef UINT_MAX
#define UINT_MAX    (~0U)
#endif
#ifndef LONG_MAX
#define LONG_MAX    ((long)(~0UL>>1))
#endif
#ifndef LONG_MIN
#define LONG_MIN    (-LONG_MAX - 1)
#endif
#ifndef ULONG_MAX
#define ULONG_MAX   (~0UL)
#endif
#ifndef LLONG_MAX
#define LLONG_MAX   ((long long)(~0ULL>>1))
#endif
#ifndef LLONG_MIN
#define LLONG_MIN   (-LLONG_MAX - 1)
#endif
#ifndef ULLONG_MAX
#define ULLONG_MAX  (~0ULL)
#endif

#ifndef DATA_TYPE_X_BOOL
#define DATA_TYPE_X_BOOL
typedef enum
{
#ifndef FALSE
    FALSE = 0,
#endif
#ifndef NO
    NO = 0,
#endif
#ifndef ZERO
    ZERO = 0,
#endif
#ifndef TRUE
    TRUE = 1,
#endif
#ifndef YES
    YES = 1,
#endif
#ifndef ONE
    ONE = 1,
#endif
#ifndef OK
    OK = 0,
#endif
#ifndef FAIL
    FAIL = -1,
#endif
} BOOL;
#endif
/*
 * Check at compile time that something is of a particular type.
 * Always evaluates to 1 so you may use it easily in comparisons.
 */
#define typecheck(type,x) \
    ({  type __dummy; \
        typeof(x) __dummy2; \
        (void)(&__dummy == &__dummy2); \
        1; \
    })

static inline int is_power_of_2(unsigned long n)
{
    return (n != 0 && ((n & (n - 1)) == 0));
}

/* round "x" up/down to next multiple of "align" (which must be a power of 2) */
#define ROUND_UP(x, align)                                   \
    (((unsigned long)(x) + ((unsigned long)(align) - 1)) & \
     ~((unsigned long)(align) - 1))
#define ROUND_DOWN(x, align)                                 \
    ((unsigned long)(x) & ~((unsigned long)(align) - 1))

//#define DIV_ROUND_UP(n,d)  (((n) + (d) - 1) / (d))

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static inline int test_bit(int nr, long *addr)
{
    int mask;
    addr += nr >> 5;
    mask = 1 << (nr & 0x1f);
    return ((mask & *addr) != 0);
}

/*
 * These functions are the basis of our bit ops.
 *
 * First, the atomic bitops. These use native endian.
 */
static inline void set_bit(unsigned int bit, volatile unsigned long *p)
{
    unsigned long flags;
    unsigned long mask = 1UL << (bit & 31);
    p += bit >> 5;
    ENTER_CRITICAL(flags);
    *p |= mask;
    EXIT_CRITICAL(flags);
}

static inline void clear_bit(unsigned int bit, volatile unsigned long *p)
{
    unsigned long flags;
    unsigned long mask = 1UL << (bit & 31);
    p += bit >> 5;
    ENTER_CRITICAL(flags);
    *p &= ~mask;
    EXIT_CRITICAL(flags);
}

static inline void change_bit(unsigned int bit, volatile unsigned long *p)
{
    unsigned long flags;
    unsigned long mask = 1UL << (bit & 31);
    p += bit >> 5;
    ENTER_CRITICAL(flags);
    *p ^= mask;
    EXIT_CRITICAL(flags);
}

static inline int test_and_set_bit(unsigned int bit, volatile unsigned long *p)
{
    unsigned long flags;
    unsigned int res;
    unsigned long mask = 1UL << (bit & 31);
    p += bit >> 5;
    ENTER_CRITICAL(flags);
    res = *p;
    *p = res | mask;
    EXIT_CRITICAL(flags);
    return res & mask;
}

static inline int test_and_clear_bit(unsigned int bit, volatile unsigned long *p)
{
    unsigned long flags;
    unsigned int res;
    unsigned long mask = 1UL << (bit & 31);
    p += bit >> 5;
    ENTER_CRITICAL(flags);
    res = *p;
    *p = res & ~mask;
    EXIT_CRITICAL(flags);
    return res & mask;
}

static inline int test_and_change_bit(unsigned int bit, volatile unsigned long *p)
{
    unsigned long flags;
    unsigned int res;
    unsigned long mask = 1UL << (bit & 31);
    p += bit >> 5;
    ENTER_CRITICAL(flags);
    res = *p;
    *p = res ^ mask;
    EXIT_CRITICAL(flags);
    return res & mask;
}

/* -------------------------------- jiffies -----------------------------*/
#define HZ 100
#define jiffies ((unsigned long)rt_tick_get())

/*
 *  These inlines deal with timer wrapping correctly. You are
 *  strongly encouraged to use them
 *  1. Because people otherwise forget
 *  2. Because if the timer wrap changes in future you won't have to
 *     alter your driver code.
 *
 * time_after(a,b) returns true if the time a is after time b.
 *
 * Do this with "<0" and ">=0" to only test the sign of the result. A
 * good compiler would generate better code (and a really good compiler
 * wouldn't care). Gcc is currently neither.
 */
#define time_after(a,b)     \
    (typecheck(unsigned long, a) && \
     typecheck(unsigned long, b) && \
     ((int)(b) - (int)(a) < 0))
#define time_before(a,b)    time_after(b,a)

#define time_after_eq(a,b)  \
    (typecheck(unsigned long, a) && \
     typecheck(unsigned long, b) && \
     ((int)(a) - (int)(b) >= 0))
#define time_before_eq(a,b) time_after_eq(b,a)

#endif /* __SUPPORT_H__ */
