#include "sdhci_wait.h"

void __init_waitqueue_head(struct wait_queue_head *wq_head, const char *name)
{
    rt_wqueue_init(&wq_head->head);
}

void __wake_up(struct wait_queue_head *wq_head, unsigned int mode,
            int nr_exclusive, void *key)
{
    rt_wqueue_wakeup(&wq_head->head, key);
}
