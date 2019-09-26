#ifndef __LINUX_WORKQUEUE_H__
#define __LINUX_WORKQUEUE_H__

/* We don't do this yet */
#if defined (__GNUC__)    
struct work_struct { } ;
#elif defined (MSVC)
struct work_struct {int no; } ;
#else
#error "please use a right C compiler"
#endif


#define INIT_WORK(x,y,z) /* */
#define schedule_work(x) do { } while(0)
#define flush_scheduled_work() do { } while(0)

#endif /* __LINUX_WORKQUEUE_H__ */
