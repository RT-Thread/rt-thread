#ifndef __ASM_SEMAPHORE_H__
#define __ASM_SEMAPHORE_H__

//#include <cyg/hal/drv_api.h>

//struct semaphore {
//	cyg_drv_mutex_t x;
//};

//#define DECLARE_MUTEX(x) //struct semaphore x = { { 0 } };
//#define DECLARE_MUTEX_LOCKED(x) //struct semaphore x = { { 1 } };
//
//#define init_MUTEX(sem) //cyg_drv_mutex_init((cyg_drv_mutex_t *)sem)
//#define init_MUTEX_LOCKED(sem) //do { cyg_drv_mutex_init((cyg_drv_mutex_t *)sem); cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem); } while(0)
//#define down(sem) //cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem)
//#define down_interruptible(sem) //({ cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem), 0; })
//#define down_trylock(sem) //cyg_drv_mutex_trylock((cyg_drv_mutex_t *)sem)
//#define up(sem) //cyg_drv_mutex_unlock((cyg_drv_mutex_t *)sem)

#include <rtthread.h>

struct semaphore {
	struct rt_mutex x;
};

#define DECLARE_MUTEX(x) struct semaphore x = { { .value = 0, } };
#define DECLARE_MUTEX_LOCKED(x) struct semaphore x = { { .vlalue = 1 } };

#define init_MUTEX(sem) rt_mutex_init((rt_mutex_t *)sem, "mutex", RT_IPC_FLAG_FIFO)
#define init_MUTEX_LOCKED(sem) do { \
		rt_mutex_init((rt_mutex_t *)sem, "mutex", RT_IPC_FLAG_FIFO);\
		rt_mutex_take((rt_mutex_t *)sem,  RT_WAITING_FOREVER);} \
		while(0)
#define down(sem) rt_mutex_take((rt_mutex_t *)sem,  RT_WAITING_FOREVER)
#define down_interruptible(sem) ({rt_mutex_take((rt_mutex_t *)sem,  RT_WAITING_FOREVER), 0; })
/*
Attempt to lock the mutex pointed to by the mutex argument without waiting. 
If the mutex is already locked by some other thread then this function 
returns FALSE. If the function can lock the mutex without waiting, then 
TRUE is returned. 
void cyg_drv_mutex_unlock( cyg_drv_mutex *mutex )
*/

#define down_trylock(sem) rt_mutex_take((rt_mutex_t *)sem,  RT_WAITING_NO)
#define up(sem) rt_mutex_release((rt_mutex_t *)sem)
#endif /* __ASM_SEMAPHORE_H__ */
