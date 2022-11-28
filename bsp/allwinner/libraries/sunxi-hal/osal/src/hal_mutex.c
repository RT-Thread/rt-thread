#include <stdlib.h>
#include <hal_mutex.h>

#define PEND_TICK_MAX (0x7FFFFFFF - 1)
#define HAL_MUTEX_OK 0

hal_mutex_t hal_mutex_create(void)
{
    return rt_mutex_create("hal_mutex", RT_IPC_FLAG_FIFO);
}

int hal_mutex_delete(hal_mutex_t mutex)
{
    if (!mutex)
    {
        return -1;
    }
    return rt_mutex_delete(mutex);
}

int hal_mutex_lock(hal_mutex_t mutex)
{
    if (!mutex)
    {
        return -1;
    }
    return rt_mutex_take(mutex, PEND_TICK_MAX);
}

int hal_mutex_unlock(hal_mutex_t mutex)
{
    if (!mutex)
    {
        return -1;
    }
    return rt_mutex_release(mutex);
}

int hal_mutex_trylock(hal_mutex_t mutex)
{
    if (!mutex)
    {
        return -1;
    }
    if (rt_mutex_take(mutex, 0) == 0)
    {
        return 0;
    }
    return -2;
}

int hal_mutex_timedwait(hal_mutex_t mutex, int ticks)
{
    if (!mutex)
    {
        return -1;
    }
    return rt_mutex_take(mutex, ticks);
}
