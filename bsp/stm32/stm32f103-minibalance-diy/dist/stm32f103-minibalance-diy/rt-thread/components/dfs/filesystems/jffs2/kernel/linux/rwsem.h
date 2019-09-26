#ifndef __LINUX_RWSEM_H__
#define __LINUX_RWSEM_H__

// eCos does not have the concept of a read/write semaphore. So just
// map them onto normal semaphores and hope we don't deadlock
// somewhere.

#include <asm/semaphore.h>

struct rw_semaphore;

#define down_read(sem) cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem)
#define down_read_trylock(sem) cyg_drv_mutex_trylock((cyg_drv_mutex_t *)sem)
#define down_write(sem) cyg_drv_mutex_lock((cyg_drv_mutex_t *)sem)
#define down_write_trylock(sem) cyg_drv_mutex_trylock((cyg_drv_mutex_t *)sem)
#define up_read(sem) cyg_drv_mutex_unlock((cyg_drv_mutex_t *)sem)
#define up_write(sem) cyg_drv_mutex_unlock((cyg_drv_mutex_t *)sem)
#define downgrade_write(sem) 

#endif // __LINUX_RWSEM_H__ 
