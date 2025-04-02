/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <riscv_io.h>
#include <string.h>
#include "ioremap.h"
#include "board.h"
#include "drv_hardlock.h"
#include <rtdbg.h>

#define DBG_TAG  "HARDLOCK"

#ifdef RT_DEBUG
#define DBG_LVL          DBG_LOG
#else
#define DBG_LVL          DBG_WARNING
#endif
#define DBG_COLOR

struct device_hardlock
{
    volatile void *hw_base;
    char used[HARDLOCK_MAX];
};
static struct device_hardlock  hardlock;

int kd_hardlock_lock(hardlock_type num)
{
    if(num < 0 || num >= HARDLOCK_MAX)
        return -1;

    if(!readl(hardlock.hw_base + num * 0x4))
    {
        LOG_D("hardlock-%d locked\n", num);
        return 0;
    }

    LOG_D("hardlock-%d is busy\n", num);
    return -1;
}
RTM_EXPORT(kd_hardlock_lock);

void kd_hardlock_unlock(hardlock_type num)
{
    if(num < 0 || num >= HARDLOCK_MAX)
        return;

    if(readl(hardlock.hw_base + num * 0x4))
    {
        writel(0x0, hardlock.hw_base + num * 0x4);
    }
    LOG_D("hardlock-%d unlock\n", num);
}
RTM_EXPORT(kd_hardlock_unlock);

int kd_request_lock(hardlock_type num)
{
    if(num < 0 || num >= HARDLOCK_MAX)
        return -1;

    if(!hardlock.used[num])
    {
        hardlock.used[num] = 1;
        return 0;
    }

    LOG_E("request hardlock failed, hardlock-%d is used\n", num);
    return -1;
}
RTM_EXPORT(kd_request_lock);

int rt_hw_hardlock_init(void)
{
    struct device_hardlock  *hard = &hardlock;
    hard->hw_base = 0xA0 + rt_ioremap((void *)MAILBOX_BASE_ADDR, MAILBOX_IO_SIZE);
    if(hard->hw_base == RT_NULL)
    {
        rt_kprintf("hardlock ioremap error\n");
        return -1;
    }

    memset(hard->used, 0, sizeof(hard->used));
#if 0
    rt_kprintf("canaan hardlock init OK\n");
#endif
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_hardlock_init);