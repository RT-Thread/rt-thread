#include <rtthread.h>
#include <ipc/waitqueue.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include "poll.h"


#include "inc/drm_device.h"
#include "inc/drm_file.h"

int drm_event_reserve(struct drm_device* dev, struct drm_pending_event* p,
                      struct drm_event* e)
{
    p->event = e;
    rt_list_insert_before(&dev->pending_event_list,&p->pending_link);
    p->dev = dev;
    return 0;
}

void drm_send_event(struct drm_device* dev, struct drm_pending_event* e)
{
    if (!e->dev) {
        rt_free(e);
        return;
    }
    rt_list_remove(&e->pending_link);
    rt_list_insert_after(&dev->event_list,&e->link);

    dev->tick = RT_TRUE;
    rt_wqueue_wakeup(&dev->drm_queue, (void *)POLLIN);

}

