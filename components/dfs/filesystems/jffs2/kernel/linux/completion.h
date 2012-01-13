#ifndef __LINUX_COMPLETION_H__
#define __LINUX_COMPLETION_H__

#if defined (__GNUC__)    
struct completion { } ;
#elif defined (MSVC)
struct completion {int no; } ;
#else
#error "please use a right C compiler"
#endif

#endif /* __LINUX_COMPLETION_H__ */

