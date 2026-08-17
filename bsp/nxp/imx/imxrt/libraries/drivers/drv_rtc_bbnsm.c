/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-14     nxp-ran      First version for MIMXRT1180 CM33 BBNSM RTC.
 * 2026-08-16     nxp-ran      v2: use real BBNSM 32768 Hz hardware counter
 *                             with GPR-based sync point for time offset.
 */

/*
 * RT-Thread RTC driver for MIMXRT1180 CM33 -- BBNSM-based.
 *
 * Hardware constraints (RT1180 specific):
 *   - The RT1180 has BBNSM (Battery-Backed Non-Secure Module) instead of SNVS.
 *   - The BBNSM RTC is a 47-bit free-running counter at 32.768 kHz (32768 Hz).
 *   - BBNSM_RTC_LS[31:0] holds lower counter bits; BBNSM_RTC_MS[14:0] upper.
 *   - Writes to BBNSM_RTC_LS/MS are blocked by ELE firmware even from CM33
 *     secure world.  We therefore CANNOT set the hardware counter directly.
 *   - BBNSM GPR[0..7] are 8x 32-bit battery-backed SRAM registers that
 *     survive warm resets (NVIC reset, watchdog, reset button) as long as
 *     VDD_BBSM is powered.  These registers CAN be read and written freely.
 *
 * Time-keeping strategy (sync-point / offset method):
 *   A sync point is stored in BBNSM GPR registers:
 *     GPR[0] = epoch_base  : Unix seconds at the last SET_TIME call.
 *     GPR[1] = snap_lo     : lower 32 bits of BBNSM RTC ticks at sync.
 *     GPR[2] = snap_hi     : upper bits  of BBNSM RTC ticks at sync.
 *     GPR[3] = magic       : 0xBBCC0002 -- marks valid GPR contents.
 *
 *   GET_TIME computes:
 *     current = epoch_base + (bbnsm_ticks_now - snap_ticks) / 32768
 *
 *   This gives monotonically increasing time that:
 *     - Uses the hardware 32768 Hz counter for sub-second accuracy.
 *     - Survives warm resets (GPR retains values, counter keeps running).
 *     - Falls back to rt_tick-based delta on boards without a 32K crystal
 *       (detected when the counter is not advancing -- reads stuck at 0).
 *
 * Usage:
 *   Enable BSP_USING_RTC in menuconfig.  SOC_IMXRT1180_SERIES selects this
 *   driver automatically instead of drv_rtc.c.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>

#ifdef BSP_USING_RTC
#ifdef SOC_IMXRT1180_SERIES

#define LOG_TAG "drv.rtc"
#include <drv_log.h>

#include "drv_rtc_bbnsm.h"
#include "fsl_device_registers.h"

/* Magic value stored in BBNSM GPR[3] to detect valid warm-reset state. */
#define BBNSM_GPR_MAGIC (0xBBCC0002u)

/* BBNSM GPR array indices used by this driver. */
#define GPR_IDX_EPOCH   (0u)    /* Unix epoch seconds at last sync */
#define GPR_IDX_SNAP_LO (1u)    /* lower 32 bits of RTC ticks at sync */
#define GPR_IDX_SNAP_HI (2u)    /* upper bits  of RTC ticks at sync  */
#define GPR_IDX_MAGIC   (3u)    /* magic sentinel */

/* 32768 Hz crystal clock rate of the BBNSM RTC counter. */
#define BBNSM_RTC_FREQ (32768u)

/*
 * In-RAM copies of the sync point (loaded at init, updated on SET_TIME).
 * These avoid GPR reads on every GET_TIME call.
 */
static time_t s_epoch_base = 0;
static uint32_t s_snap_lo = 0;
static uint32_t s_snap_hi = 0;

/*
 * Fallback: rt_tick at init (used only when BBNSM RTC ticks are stuck at 0,
 * i.e. no 32K crystal populated).
 */
static rt_tick_t s_tick_base = 0;
static rt_bool_t s_use_rtc_hw = RT_FALSE;

/*******************************************************************************
 * Internal helpers
 ******************************************************************************/

/*
 * Read the 47-bit BBNSM RTC counter using a double-read of the MS register
 * to guard against a carry between LS and MS during the read.
 */
static uint64_t bbnsm_read_ticks(void)
{
    uint32_t ms1, ms2, ls;
    do
    {
        ms1 = BBNSM->BBNSM_RTC_MS & BBNSM_BBNSM_RTC_MS_RTC_MASK;
        ls = BBNSM->BBNSM_RTC_LS;
        ms2 = BBNSM->BBNSM_RTC_MS & BBNSM_BBNSM_RTC_MS_RTC_MASK;
    } while (ms1 != ms2);

    return ((uint64_t)ms1 << 32u) | (uint64_t)ls;
}

/*
 * Enable the BBNSM RTC counter (if it is not already running).
 * Writing 0x2 to the RTC_EN field enables it; 0x1 disables it.
 * We only set the enable bit -- we do NOT write the counter itself.
 */
static void bbnsm_rtc_enable(void)
{
    uint32_t ctrl = BBNSM->BBNSM_CTRL;
    /* Field is 2-bit: 0x2 = enable, 0x1 = disable, 0x0 = no change. */
    uint32_t en = (ctrl & BBNSM_BBNSM_CTRL_RTC_EN_MASK) >>
                  BBNSM_BBNSM_CTRL_RTC_EN_SHIFT;
    if (en != 0x2u)
    {
        BBNSM->BBNSM_CTRL = (ctrl & ~BBNSM_BBNSM_CTRL_RTC_EN_MASK) |
                            BBNSM_BBNSM_CTRL_RTC_EN(0x2u);
    }
}

/*
 * Persist the sync point to BBNSM GPR registers.
 * Magic is cleared first so a torn write does not leave stale values.
 */
static void bbnsm_gpr_save(time_t epoch, uint32_t snap_lo, uint32_t snap_hi)
{
    BBNSM->GPR[GPR_IDX_MAGIC] = 0u;         /* invalidate while writing */
    BBNSM->GPR[GPR_IDX_EPOCH] = (uint32_t)epoch;
    BBNSM->GPR[GPR_IDX_SNAP_LO] = snap_lo;
    BBNSM->GPR[GPR_IDX_SNAP_HI] = snap_hi;
    BBNSM->GPR[GPR_IDX_MAGIC] = BBNSM_GPR_MAGIC;
}

/*
 * Try to restore the sync point from BBNSM GPR registers.
 * Returns RT_TRUE if a valid saved state was found, RT_FALSE on cold boot.
 */
static rt_bool_t bbnsm_gpr_restore(time_t *out_epoch,
                                   uint32_t *out_snap_lo,
                                   uint32_t *out_snap_hi)
{
    if (BBNSM->GPR[GPR_IDX_MAGIC] == BBNSM_GPR_MAGIC)
    {
        *out_epoch = (time_t)BBNSM->GPR[GPR_IDX_EPOCH];
        *out_snap_lo = BBNSM->GPR[GPR_IDX_SNAP_LO];
        *out_snap_hi = BBNSM->GPR[GPR_IDX_SNAP_HI];
        return RT_TRUE;
    }
    return RT_FALSE;
}

/*******************************************************************************
 * RT-Thread device ops
 ******************************************************************************/

static rt_err_t imxrt1180_rtc_init(rt_device_t dev)
{
    (void)dev;

    /* Make sure the BBNSM RTC counter is running. */
    bbnsm_rtc_enable();

    /* Detect whether the 32K crystal is working: if the counter is
     * non-zero (or if it advances) we use the hardware ticks; otherwise
     * we fall back to rt_tick_get() delta. */
    uint64_t t0 = bbnsm_read_ticks();
    /* A simple non-zero check is sufficient: if no crystal the counter
     * will remain 0 forever. */
    s_use_rtc_hw = (t0 != 0u) ? RT_TRUE : RT_FALSE;

    if (!s_use_rtc_hw)
    {
        LOG_W("BBNSM RTC counter is 0 -- no 32K crystal? falling back to rt_tick");
    }

    /* Try to restore sync point from GPR (warm reset). */
    time_t epoch = 0;
    uint32_t snap_lo = 0;
    uint32_t snap_hi = 0;

    if (bbnsm_gpr_restore(&epoch, &snap_lo, &snap_hi))
    {
        s_epoch_base = epoch;
        s_snap_lo = snap_lo;
        s_snap_hi = snap_hi;
        s_tick_base = rt_tick_get();
        LOG_I("warm reset: RTC epoch=%u snap_hi=%u snap_lo=%u",
              (unsigned)epoch, (unsigned)snap_hi, (unsigned)snap_lo);
    }
    else
    {
        /* Cold boot: start from epoch 0; wait for a SET_TIME call. */
        s_epoch_base = 0;
        s_snap_lo = (uint32_t)(t0 & 0xFFFFFFFFu);
        s_snap_hi = (uint32_t)(t0 >> 32u);
        s_tick_base = rt_tick_get();
        LOG_I("cold boot: BBNSM GPR no valid epoch, RTC at epoch 0");
    }

    return RT_EOK;
}

static rt_err_t imxrt1180_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    (void)dev;
    (void)oflag;
    return RT_EOK;
}

static rt_err_t imxrt1180_rtc_close(rt_device_t dev)
{
    (void)dev;
    return RT_EOK;
}

static rt_ssize_t imxrt1180_rtc_read(rt_device_t dev, rt_off_t pos,
                                     void *buf, rt_size_t size)
{
    (void)dev;
    (void)pos;
    (void)buf;
    (void)size;
    return -RT_EINVAL;
}

static rt_ssize_t imxrt1180_rtc_write(rt_device_t dev, rt_off_t pos,
                                      const void *buf, rt_size_t size)
{
    (void)dev;
    (void)pos;
    (void)buf;
    (void)size;
    return -RT_EINVAL;
}

static rt_err_t imxrt1180_rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        time_t current;

        if (s_use_rtc_hw)
        {
            /* Hardware path: compute elapsed seconds from RTC tick delta. */
            uint64_t now_ticks = bbnsm_read_ticks();
            uint64_t snap_ticks = ((uint64_t)s_snap_hi << 32u) |
                                  (uint64_t)s_snap_lo;
            uint64_t delta_ticks = (now_ticks >= snap_ticks) ? (now_ticks - snap_ticks) : 0u;
            current = s_epoch_base + (time_t)(delta_ticks / BBNSM_RTC_FREQ);
        }
        else
        {
            /* Fallback path: use rt_tick delta (no 32K crystal). */
            rt_tick_t elapsed_ticks = rt_tick_get() - s_tick_base;
            current = s_epoch_base +
                      (time_t)(elapsed_ticks / RT_TICK_PER_SECOND);
        }

        *(time_t *)args = current;
        break;
    }

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        time_t new_epoch = *(time_t *)args;
        uint64_t now_ticks = bbnsm_read_ticks();
        uint32_t snap_lo = (uint32_t)(now_ticks & 0xFFFFFFFFu);
        uint32_t snap_hi = (uint32_t)(now_ticks >> 32u);

        s_epoch_base = new_epoch;
        s_snap_lo = snap_lo;
        s_snap_hi = snap_hi;
        s_tick_base = rt_tick_get();

        bbnsm_gpr_save(new_epoch, snap_lo, snap_hi);

        if (s_use_rtc_hw == RT_FALSE && now_ticks != 0u)
        {
            /* Crystal may have started since init -- re-enable hw path. */
            s_use_rtc_hw = RT_TRUE;
            LOG_I("RTC hw counter now non-zero, switching to hardware path");
        }

        LOG_D("RTC SET_TIME: epoch=%u", (unsigned)new_epoch);
        break;
    }

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

/*******************************************************************************
 * Device registration
 ******************************************************************************/

static struct rt_device s_rtc_device = {
    .type = RT_Device_Class_RTC,
    .init = imxrt1180_rtc_init,
    .open = imxrt1180_rtc_open,
    .close = imxrt1180_rtc_close,
    .read = imxrt1180_rtc_read,
    .write = imxrt1180_rtc_write,
    .control = imxrt1180_rtc_control,
};

int rt_hw_rtc_init(void)
{
    rt_err_t ret;

    ret = rt_device_register(&s_rtc_device, "rtc", RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("rtc device register failed: %d", ret);
        return ret;
    }

    ret = rt_device_open(&s_rtc_device, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("rtc device open failed: %d", ret);
        return ret;
    }

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* SOC_IMXRT1180_SERIES */
#endif /* BSP_USING_RTC */
