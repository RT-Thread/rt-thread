#include <rthw.h>
#include <rtthread.h>

#include "lwp.h"
//#include "lwp_tid.h"
#include "lwp_pid.h"

int setsid(void)
{
    int err = -EPERM;
    struct rt_thread *current_thread = rt_thread_self();
    struct rt_lwp *current_lwp = (struct rt_lwp *)rt_thread_self()->lwp;

    if (current_lwp->session == current_thread->tid)
    {
        return err;
    }

    current_lwp->session = current_thread->tid;
    current_lwp->__pgrp = current_thread->tid;
    current_lwp->leader = 1;
    current_lwp->tty = RT_NULL;
    current_lwp->tty_old_pgrp = 0;

    err = current_lwp->session;
    return err;
}
