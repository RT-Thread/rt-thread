#ifndef __LINUX_TIMER_H__
#define __LINUX_TIMER_H__

/* Not yet */

#if defined (__GNUC__)    
struct timer_list { } ;
#elif defined (MSVC)
struct timer_list {int no; } ;
#else
#error "please use a right C compiler"
#endif

#endif /* __LINUX_TIMER_H__ */

