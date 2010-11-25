/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	32

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	4

/* SECTION: IPC */
/* Using Semaphore */
#define RT_USING_SEMAPHORE

/* Using Mutex */
#define RT_USING_MUTEX

/* Using Event */
#define RT_USING_EVENT

/* Using MailBox */
#define RT_USING_MAILBOX

/* Using Message Queue */
#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
#define RT_USING_MEMPOOL

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE

/* Using Module System */
#define RT_USING_MODULE

/* name length of RTGUI object */
#define RTGUI_NAME_MAX		16
#endif
