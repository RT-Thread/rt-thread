#ifndef __LINUX_WAIT_H__
#define __LINUX_WAIT_H__


#if defined (__GNUC__)    
typedef struct { } wait_queue_head_t;
#elif defined (MSVC)
typedef struct {int no; } wait_queue_head_t;
#else
#error "please use a right C compiler"
#endif

#define init_waitqueue_head(wait) do{} while (0)
#define add_wait_queue(wait,new_wait) do{} while (0)
#define remove_wait_queue(wait,old_wait) do{} while (0)
#define DECLARE_WAITQUEUE(wait,current) do{} while (0)

static inline void wake_up(wait_queue_head_t *erase_wait)
{ /* Only used for waking up threads blocks on erases. Not used in eCos */ }

#endif /* __LINUX_WAIT_H__ */
