#include <rtthread.h>
#include <stdio.h>

struct __lock
{
    rt_mutex_t sys_mutex;
};
typedef struct __lock* _LOCK_T;

int __retarget_lock_init(_LOCK_T *lock)
{
    static int mutex_counter = 0;
    char mutex_name[20];

    (*lock) = rt_malloc(sizeof(struct __lock));

    (*lock)->sys_mutex = NULL;

    snprintf(mutex_name, 20, "libc_mutex%d", mutex_counter++);
    (*lock)->sys_mutex = rt_mutex_create(mutex_name, 0);
    if(!((*lock)->sys_mutex))
    {
        rt_free((*lock));
        return -RT_ERROR;
    }

    return RT_EOK;
}

int __retarget_lock_init_recursive(_LOCK_T *lock)
{
    return __retarget_lock_init(lock);
}

int __retarget_lock_deinit(_LOCK_T lock)
{
    int ret = 0;

    if(lock)
    {
        ret = rt_mutex_delete((rt_mutex_t)lock->sys_mutex);
        rt_free(lock);
        return ret;
    }

    return -RT_ERROR;
}

int __retarget_lock_deinit_recursive(_LOCK_T lock)
{
    return __retarget_lock_deinit(lock);
}

int __retarget_lock_take(_LOCK_T lock)
{
    if(lock)
        return rt_mutex_take(lock->sys_mutex, 0);

    return -RT_ERROR;
}

int __retarget_lock_take_recursive(_LOCK_T lock)
{
    return __retarget_lock_take(lock);
}

int __retarget_lock_release(_LOCK_T lock)
{
    if(lock)
        return rt_mutex_release(lock->sys_mutex);

    return -RT_ERROR;
}

int __retarget_lock_release_recursive(_LOCK_T lock)
{
    return __retarget_lock_release(lock);
}

int *__errno_location(void)
{
    return _rt_errno();
}
