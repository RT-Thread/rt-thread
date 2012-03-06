#ifndef __ASM_SEMAPHORE_H__
#define __ASM_SEMAPHORE_H__

#define CONFIG_JFFS2_SEMAPHORE  1 // no mutex, 1 use static, 2 use dynamic
#if CONFIG_JFFS2_SEMAPHORE == 0
#include <cyg/hal/drv_api.h>

struct semaphore {
	cyg_drv_mutex_t x;
};

#define DECLARE_MUTEX(x) //struct semaphore x = { { 0 } };
#define DECLARE_MUTEX_LOCKED(x) //struct semaphore x = { { 1 } };

#define init_MUTEX(struct semaphore * sem)  //cyg_drv_mutex_init((cyg_drv_mutex_t *)sem)
#define init_MUTEX_LOCKED(struct semaphore * sem)  //do { cyg_drv_mutex_init((cyg_drv_mutex_t *)sem); cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem); } while(0)
#define down(struct semaphore * sem)  //cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem)
#define down_interruptible(struct semaphore * sem)  0//({ cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem), 0; })
#define down_trylock(struct semaphore * sem)  //cyg_drv_mutex_trylock((cyg_drv_mutex_t *)sem)
#define up(struct semaphore * sem)  //cyg_drv_mutex_unlock((cyg_drv_mutex_t *)sem)

#elif CONFIG_JFFS2_SEMAPHORE == 1
#include <rtthread.h>

struct semaphore {
	struct rt_mutex mutex;
};

#define DECLARE_MUTEX(x)
#define DECLARE_MUTEX_LOCKED(x)
rt_inline void init_MUTEX(struct semaphore * sem)
{
   if (rt_mutex_init((rt_mutex_t)sem, "mutex", RT_IPC_FLAG_FIFO) == RT_EOK)
   {
	   /* detach the object from system object container */
	   rt_object_detach(&(((rt_mutex_t)sem)->parent.parent));
	   return;
   }
   rt_kprintf("get an error at %s:%d \n",  __FUNCTION__, __LINE__);
   RT_ASSERT(0);
}

rt_inline void init_MUTEX_LOCKED(struct semaphore * sem)
{
   if (rt_mutex_init((rt_mutex_t)sem, "mutex", RT_IPC_FLAG_FIFO) == RT_EOK)
   {
	   /* detach the object from system object container */
	   rt_object_detach(&(((rt_mutex_t)sem)->parent.parent));
	   rt_mutex_take((rt_mutex_t)sem, RT_WAITING_FOREVER);
	   return;
   }
   rt_kprintf("get an error at %s:%d \n",  __FUNCTION__, __LINE__);
   RT_ASSERT(0);
}
/*
rt_inline void init_MUTEX(struct semaphore * sem)
{
	if (rt_mutex_init((rt_mutex_t)sem, "mutex", RT_IPC_FLAG_FIFO) == RT_EOK)
		return;
	rt_kprintf("get an error at %s:%d \n",  __FUNCTION__, __LINE__);
	RT_ASSERT(0);
}

rt_inline init_MUTEX_LOCKED(struct semaphore * sem)
{
	if (rt_mutex_init((rt_mutex_t)sem, "mutex", RT_IPC_FLAG_FIFO) == RT_EOK)
	{
		rt_mutex_take((rt_mutex_t)sem, RT_WAITING_FOREVER);
		return;
	}
	rt_kprintf("get an error at %s:%d \n",  __FUNCTION__, __LINE__);
	RT_ASSERT(0);
}
*/
rt_inline down(struct semaphore * sem)
{
	rt_mutex_take((rt_mutex_t)sem, RT_WAITING_FOREVER);
}
rt_inline int down_interruptible(struct semaphore* sem)
{
	rt_mutex_take((rt_mutex_t)sem, RT_WAITING_FOREVER);
    return 0;
}
rt_inline up(struct semaphore * sem)
{
	rt_mutex_release((rt_mutex_t)sem);
}
#elif CONFIG_JFFS2_SEMAPHORE == 2

#include <rtthread.h>

struct semaphore {
	 rt_mutex_t mutex;
};

#define DECLARE_MUTEX(x)
#define DECLARE_MUTEX_LOCKED(x)

rt_inline void init_MUTEX(struct semaphore * sem)
{
	sem->mutex = rt_mutex_create("mutex", RT_IPC_FLAG_FIFO);
}
rt_inline init_MUTEX_LOCKED(struct semaphore * sem)
{
	sem->mutex = rt_mutex_create("mutex", RT_IPC_FLAG_FIFO);
	rt_mutex_take(sem->mutex,  RT_WAITING_FOREVER);
}
rt_inline down(struct semaphore * sem)
{
	rt_mutex_take(sem->mutex,  RT_WAITING_FOREVER);
}
rt_inline int down_interruptible(struct semaphore* sem)
{
	rt_mutex_take(sem->mutex,  RT_WAITING_FOREVER);
    return 0;
}
/*
Attempt to lock the mutex pointed to by the mutex argument without waiting. 
If the mutex is already locked by some other thread then this function 
returns FALSE. If the function can lock the mutex without waiting, then 
TRUE is returned. 
void cyg_drv_mutex_unlock( cyg_drv_mutex *mutex )
*/

//#define down_trylock(struct semaphore * sem)  rt_mutex_take((rt_mutex_t)sem,  RT_WAITING_NO)
rt_inline up(struct semaphore * sem)
{
	rt_mutex_release(sem->mutex);
}

#else
#error "CONFIG_JFFS2_SEMAPHORE should be 0, 1 or 2"
#endif

#endif /* __ASM_SEMAPHORE_H__ */
