/*
 * ===========================================================================================
 *
 *       Filename:  hal_timer.c
 *
 *    Description:  osal timer glue layer for hal.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-26 20:21:27
 *       Revision:  none
 *       Compiler:  GCC:version 7.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2019-12-17 18:10:51
 *
 * ===========================================================================================
 */

#include <hal_timer.h>

osal_timer_t osal_timer_create(const char *name,
                               timeout_func timeout,
                               void *parameter,
                               unsigned int time,
                               unsigned char flag)
{
    return rt_timer_create(name, timeout, parameter, time, flag);
}

int osal_timer_delete(osal_timer_t timer)
{
    return rt_timer_delete(timer);
}

int osal_timer_start(osal_timer_t timer)
{
    return rt_timer_start(timer);
}

int osal_timer_stop(osal_timer_t timer)
{
    return rt_timer_stop(timer);
}

int osal_timer_control(osal_timer_t timer, int cmd, void *arg)
{
    return rt_timer_control(timer, cmd, arg);
}

void sleep(int seconds);
int msleep(unsigned int msecs);
int usleep(unsigned int usecs);

int hal_sleep(unsigned int secs)
{
    sleep(secs);
    return 0;
}

int hal_msleep(unsigned int msecs)
{
    return msleep(msecs);
}

int hal_usleep(unsigned int usecs)
{
    return usleep(usecs);
}


