
/* Copyright Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <rtthread.h>
#include "dmalock.h"

struct dmac_host
{
    struct rt_semaphore sem;
    struct rt_mutex mutex;
    uint8_t channel_used[DMAC_CHANNEL_COUNT];
    char *channel_name[DMAC_CHANNEL_COUNT];
};

static struct dmac_host _dmac_host;

void dmalock_init(void)
{
    rt_sem_init(&_dmac_host.sem, "dma_sem", DMAC_CHANNEL_COUNT, RT_IPC_FLAG_FIFO);
    rt_mutex_init(&_dmac_host.mutex, "dma_mutex", RT_IPC_FLAG_PRIO);
    for (int i = 0; i < DMAC_CHANNEL_COUNT; i++)
    {
        _dmac_host.channel_used[i] = 0;
        _dmac_host.channel_name[i] = NULL;
    }
}

int _dmalock_sync_take(dmac_channel_number_t *chn, int timeout_ms, const char *name)
{
    rt_err_t result;

    *chn = DMAC_CHANNEL_MAX;
    result = rt_sem_take(&_dmac_host.sem, timeout_ms);
    if (result == RT_EOK)
    {
        rt_mutex_take(&_dmac_host.mutex, RT_WAITING_FOREVER);
        for (int i = 0; i < DMAC_CHANNEL_COUNT; i++)
        {
            if (_dmac_host.channel_used[i] == 0)
            {
                _dmac_host.channel_used[i] = 1;
                _dmac_host.channel_name[i] = name;
                *chn = i;
                break;
            }
        }
        rt_mutex_release(&_dmac_host.mutex);
    }
    return result;
}

void dmalock_release(dmac_channel_number_t chn)
{
    if (chn >= DMAC_CHANNEL_MAX)
        return;
    _dmac_host.channel_name[chn] = NULL;
    _dmac_host.channel_used[chn] = 0;
    rt_sem_release(&_dmac_host.sem);
}

static void dma_ch_info(int argc, char **argv)
{
    uint32_t cnt = 0;

    for (int i = 0; i < DMAC_CHANNEL_COUNT; i++)
    {
        if (_dmac_host.channel_used[i] != 0)
        {
            rt_kprintf("dma_ch%d is using by func [%s]\n", i, _dmac_host.channel_name[i]);
            cnt++;
        }
    }

    if(cnt == 0)
        rt_kprintf(" no dma_ch is using.\n");
}
MSH_CMD_EXPORT(dma_ch_info, list dma channel informationn.);
