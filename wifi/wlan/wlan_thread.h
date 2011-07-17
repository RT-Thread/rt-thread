/*
 * Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */

#ifndef	__WLAN_THREAD_H_
#define	__WLAN_THREAD_H_

#include <rtthread.h>
#define WakeUpMainThread  (0x01)
#define WakeUpReassociationThread (0x02)
typedef struct
{
	struct   rt_thread task; //wait for modified
    struct rt_event  waitQ;
    int priority;
    void *priv;
} wlan_thread;

static void wlan_activate_thread(wlan_thread * thr)
{
    /** Record the thread pid */
	rt_event_init(&thr->waitQ, "threadevt", RT_IPC_FLAG_FIFO);
}

static  void wlan_deactivate_thread(wlan_thread * thr)
{
}

static  void wlan_create_thread(int (*wlanfunc) (void *), wlan_thread * thr, char *name)
{
   // thr->task = kthread_run(wlanfunc, thr, "%s", name);
}

static  int wlan_terminate_thread(wlan_thread * thr)
{

    return 0;
}

#endif
