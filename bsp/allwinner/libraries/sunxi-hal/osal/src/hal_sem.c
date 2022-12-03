/*
 * ===========================================================================================
 *
 *       Filename:  hal_sem.c
 *
 *    Description:  sem impl for hal driver.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-27 14:20:53
 *       Revision:  none
 *       Compiler:  GCC:version 7.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2019-11-27 17:51:06
 *
 * ===========================================================================================
 */

#include <hal_sem.h>
#include <rtdef.h>
#include <log.h>

hal_sem_t hal_sem_create(unsigned int cnt)
{
     return (hal_sem_t) rt_sem_create("hal_layer", cnt, RT_IPC_FLAG_FIFO);
}

int hal_sem_delete(hal_sem_t sem)
{
    if (sem == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    rt_sem_delete(sem);
    return 0;
}

int hal_sem_getvalue(hal_sem_t sem, int *val)
{
    if (sem == NULL || val == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    rt_sem_control(sem, RT_IPC_CMD_GET_STATE, val);

    return 0;
}

int hal_sem_post(hal_sem_t sem)
{
    if (sem == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    // must be success.
    rt_sem_release(sem);

    return 0;
}

int hal_sem_timedwait(hal_sem_t sem, int ticks)
{
    rt_err_t ret;

    if (sem == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_sem_take(sem, ticks);
    if (ret != RT_EOK)
    {
        // timeout.
        return -2;
    }

    return 0;
}

int hal_sem_trywait(hal_sem_t sem)
{
    rt_err_t ret;

    if (sem == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_sem_trytake(sem);
    if (ret != RT_EOK)
    {
        // timeout.
        return -2;
    }

    return 0;
}

int hal_sem_wait(hal_sem_t sem)
{
    rt_err_t ret;

    if (sem == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_sem_take(sem, RT_WAITING_FOREVER);
    if (ret != RT_EOK)
    {
        // timeout.
        return -2;
    }

    return 0;
}

int hal_sem_clear(hal_sem_t sem)
{
    rt_err_t ret;

    if (sem == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_sem_control(sem, RT_IPC_CMD_RESET, NULL);
    if (ret != RT_EOK) {
        __err("rt_sem_control fail\n");
        return -1;
    }

    return 0;
}
