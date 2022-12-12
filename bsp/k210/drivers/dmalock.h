#ifndef __DMALOCK_H
#define __DMALOCK_H

#include <stdint.h>
#include <rtdef.h>
#include <dmac.h>

#define dmalock_sync_take(x,y) _dmalock_sync_take(x, y, __func__)

void dmalock_init(void);
int _dmalock_sync_take(dmac_channel_number_t *chn, int timeout_ms, const char *name);
void dmalock_release(dmac_channel_number_t chn);

#endif
