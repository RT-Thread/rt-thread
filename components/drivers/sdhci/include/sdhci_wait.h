#ifndef _SDHCI_WAIT_H
#define _SDHCI_WAIT_H

#include <ipc/waitqueue.h>

typedef struct wait_queue_head
{
    rt_wqueue_t head;
}wait_queue_head_t;


enum {
    WQ_UNBOUND      = 1 << 1,
    WQ_MEM_RECLAIM      = 1 << 3,
    WQ_HIGHPRI      = 1 << 4,
};

void __init_waitqueue_head(struct wait_queue_head *wq_head, const char *name);

void __wake_up(struct wait_queue_head *wq_head, unsigned int mode,
            int nr_exclusive, void *key);

#define wake_up(x)          __wake_up(x, 0, 1, NULL)

#define init_waitqueue_head(wq_head) __init_waitqueue_head((wq_head), #wq_head)
#define wait_event_interruptible(wq_head, condition) rt_wqueue_wait(&(wq_head.head), condition, -1)
#define wait_event_timeout(wq_head, condition, timeout) ({pr_todo(); 0;})


#endif
