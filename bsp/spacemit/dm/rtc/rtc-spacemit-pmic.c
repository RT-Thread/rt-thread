/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "rtc.spacemit-pmic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rtc_dm.h"

#define __SPACEMIT_RTC_INTERNAL
#include <mfd/spacemit-pmic.h>

struct spacemit_pmic_rtc
{
    struct rt_device parent;

    int irq;
    struct spacemit_pmic *pmic;
    const struct spacemit_pmic_rtc_regdesc *desc;
};

#define raw_to_spacemit_pmic_rtc(raw) rt_container_of(raw, struct spacemit_pmic_rtc, parent)

static rt_err_t spacemit_pmic_rtc_read_time(struct spacemit_pmic_rtc *pmic_rtc, time_t *sec)
{
    unsigned int v[6], pre_v[6] = {0};
    struct tm tm;
    struct spacemit_pmic *pmic = pmic_rtc->pmic;

    if ((signed)(pre_v[0] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_s.reg)) < 0)
    {
        LOG_E("Failed to read second: %s", rt_strerror(pre_v[0]));
        return -RT_EINVAL;
    }

    if ((signed)(pre_v[1] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_mi.reg)) < 0)
    {
        LOG_E("Failed to read minute: %s", rt_strerror(pre_v[1]));
        return -RT_EINVAL;
    }

    if ((signed)(pre_v[2] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_h.reg)) < 0)
    {
        LOG_E("Failed to read hour: %s", rt_strerror(pre_v[2]));
        return -RT_EINVAL;
    }

    if ((signed)(pre_v[3] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_d.reg)) < 0)
    {
        LOG_E("Failed to read day: %s", rt_strerror(pre_v[3]));
        return -RT_EINVAL;
    }

    if ((signed)(pre_v[4] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_mo.reg)) < 0)
    {
        LOG_E("Failed to read month: %s", rt_strerror(pre_v[4]));
        return -RT_EINVAL;
    }

    if ((signed)(pre_v[5] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_y.reg)) < 0)
    {
        LOG_E("Failed to read year: %s", rt_strerror(pre_v[5]));
        return -RT_EINVAL;
    }

    while (RT_TRUE)
    {
        if ((signed)(v[0] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_s.reg)) < 0)
        {
            LOG_E("Failed to read second: %s", rt_strerror(v[0]));
            return -RT_EINVAL;
        }

        if ((signed)(v[1] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_mi.reg)) < 0)
        {
            LOG_E("Failed to read minute: %s", rt_strerror(v[1]));
            return -RT_EINVAL;
        }

        if ((signed)(v[2] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_h.reg)) < 0)
        {
            LOG_E("Failed to read hour: %s", rt_strerror(v[2]));
            return -RT_EINVAL;
        }

        if ((signed)(v[3] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_d.reg)) < 0)
        {
            LOG_E("Failed to read day: %s", rt_strerror(v[3]));
            return -RT_EINVAL;
        }

        if ((signed)(v[4] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_mo.reg)) < 0)
        {
            LOG_E("Failed to read month: %s", rt_strerror(v[4]));
            return -RT_EINVAL;
        }

        if ((signed)(v[5] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_y.reg)) < 0)
        {
            LOG_E("Failed to read year: %s", rt_strerror(v[5]));
            return -RT_EINVAL;
        }

        if ((pre_v[0] == v[0]) && (pre_v[1] == v[1]) &&
            (pre_v[2] == v[2]) && (pre_v[3] == v[3]) &&
            (pre_v[4] == v[4]) && (pre_v[5] == v[5]))
        {
            break;
        }
        else
        {
            pre_v[0] = v[0];
            pre_v[1] = v[1];
            pre_v[2] = v[2];
            pre_v[3] = v[3];
            pre_v[4] = v[4];
            pre_v[5] = v[5];
        }
    }

    tm.tm_sec = v[0] & pmic_rtc->desc->cnt_s.msk;
    tm.tm_min = v[1] & pmic_rtc->desc->cnt_mi.msk;
    tm.tm_hour = v[2] & pmic_rtc->desc->cnt_h.msk;
    tm.tm_mday = (v[3] & pmic_rtc->desc->cnt_d.msk) + 1;
    tm.tm_mon = (v[4] & pmic_rtc->desc->cnt_mo.msk);
    tm.tm_year = (v[5] & pmic_rtc->desc->cnt_y.msk) + 100;

    *sec = mktime(&tm);

    return RT_EOK;
}

static rt_err_t spacemit_pmic_rtc_set_time(struct spacemit_pmic_rtc *pmic_rtc, time_t *sec)
{
    rt_err_t err;
    unsigned int v[6];
    struct tm *tm;
    union spacemit_pmic_rtc_ctl_desc rtc_ctl;
    struct spacemit_pmic *pmic = pmic_rtc->pmic;

    tm = localtime(sec);

    if ((signed)(rtc_ctl.val = spacemit_pmic_read(pmic, pmic_rtc->desc->rtc_ctl.reg)) < 0)
    {
        LOG_E("Failed to read rtc ctrl: %s", rt_strerror(rtc_ctl.val));
        return -RT_EINVAL;
    }

    /* Disbale rtc first */
    rtc_ctl.bits.rtc_en = 0;

    if ((err = spacemit_pmic_write_bit(pmic, pmic_rtc->desc->rtc_ctl.reg, 0xff, rtc_ctl.val)))
    {
        LOG_E("Failed to set rtc ctrl register: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    while (RT_TRUE)
    {
        if ((err = spacemit_pmic_write_bit(pmic,
            pmic_rtc->desc->cnt_s.reg, pmic_rtc->desc->cnt_s.msk, tm->tm_sec)))
        {
            LOG_E("Failed to update second: %s", rt_strerror(err));
            return -RT_EINVAL;
        }

        if ((err = spacemit_pmic_write_bit(pmic,
            pmic_rtc->desc->cnt_mi.reg, pmic_rtc->desc->cnt_mi.msk, tm->tm_min)))
        {
            LOG_E("Failed to update minutes: %s", rt_strerror(err));
            return -RT_EINVAL;
        }

        if ((err = spacemit_pmic_write_bit(pmic,
            pmic_rtc->desc->cnt_h.reg, pmic_rtc->desc->cnt_h.msk, tm->tm_hour)))
        {
            LOG_E("Failed to update hour: %s", rt_strerror(err));
            return -RT_EINVAL;
        }

        if ((err = spacemit_pmic_write_bit(pmic,
            pmic_rtc->desc->cnt_d.reg, pmic_rtc->desc->cnt_d.msk, tm->tm_mday - 1)))
        {
            LOG_E("Failed to update day: %s", rt_strerror(err));
            return -RT_EINVAL;
        }

        if ((err = spacemit_pmic_write_bit(pmic,
            pmic_rtc->desc->cnt_mo.reg, pmic_rtc->desc->cnt_mo.msk, tm->tm_mon)))
        {
            LOG_E("Failed to update month: %s", rt_strerror(err));
            return -RT_EINVAL;
        }

        if ((err = spacemit_pmic_write_bit(pmic,
            pmic_rtc->desc->cnt_y.reg, pmic_rtc->desc->cnt_y.msk, tm->tm_year - 100)))
        {
            LOG_E("Failed to update month: %s", rt_strerror(err));
            return -RT_EINVAL;
        }

        /* Read again */
        if ((signed)(v[0] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_s.reg)) < 0)
        {
            LOG_E("Failed to read second: %s", rt_strerror(v[0]));
            return -RT_EINVAL;
        }
        v[0] = v[0] & pmic_rtc->desc->cnt_s.msk;

        if ((signed)(v[1] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_mi.reg)) < 0)
        {
            LOG_E("Failed to read minute: %s", rt_strerror(v[1]));
            return -RT_EINVAL;
        }
        v[1] = v[1] & pmic_rtc->desc->cnt_mi.msk;

        if ((signed)(v[2] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_h.reg)) < 0)
        {
            LOG_E("Failed to read hour: %s", rt_strerror(v[2]));
            return -RT_EINVAL;
        }
        v[2] = v[2] & pmic_rtc->desc->cnt_h.msk;

        if ((signed)(v[3] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_d.reg)) < 0)
        {
            LOG_E("Failed to read day: %s", rt_strerror(v[3]));
            return -RT_EINVAL;
        }
        v[3] = v[3] & pmic_rtc->desc->cnt_d.msk;

        if ((signed)(v[4] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_mo.reg)) < 0)
        {
            LOG_E("Failed to read month: %s", rt_strerror(v[4]));
            return -RT_EINVAL;
        }
        v[4] = v[4] & pmic_rtc->desc->cnt_mo.msk;

        if ((signed)(v[5] = spacemit_pmic_read(pmic, pmic_rtc->desc->cnt_y.reg)) < 0)
        {
            LOG_E("Failed to read year: %s", rt_strerror(v[5]));
            return -RT_EINVAL;
        }
        v[5] = v[5] & pmic_rtc->desc->cnt_y.msk;

        if ((v[0] == (pmic_rtc->desc->cnt_s.msk & tm->tm_sec)) &&
            (v[1] == (pmic_rtc->desc->cnt_mi.msk & tm->tm_min)) &&
            (v[2] == (pmic_rtc->desc->cnt_h.msk & tm->tm_hour)) &&
            ((v[3] + 1) == (pmic_rtc->desc->cnt_d.msk & tm->tm_mday)) &&
            (v[4] == (pmic_rtc->desc->cnt_mo.msk & tm->tm_mon)) &&
            (v[5] == (pmic_rtc->desc->cnt_y.msk & (tm->tm_year - 100))))
        {
            break;
        }
    }

    /* Enable rtc last */
    rtc_ctl.bits.rtc_en = 1;

    if ((err = spacemit_pmic_write_bit(pmic, pmic_rtc->desc->rtc_ctl.reg, 0xff, rtc_ctl.val)))
    {
        LOG_E("Failed to set rtc ctrl register: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t spacemit_pmic_rtc_read_alarm(struct spacemit_pmic_rtc *pmic_rtc,
        struct rt_rtc_wkalarm *alarm)
{
    unsigned int v[6];
    union spacemit_pmic_rtc_ctl_desc rtc_ctl;
    struct spacemit_pmic *pmic = pmic_rtc->pmic;

    if ((signed)(v[0] = spacemit_pmic_read(pmic, pmic_rtc->desc->alarm_s.reg)) < 0)
    {
        LOG_E("Failed to read alarm second: %s", rt_strerror(v[0]));
        return -RT_EINVAL;
    }

    if ((signed)(v[1] = spacemit_pmic_read(pmic, pmic_rtc->desc->alarm_mi.reg)) < 0)
    {
        LOG_E("Failed to read alarm minute: %s", rt_strerror(v[1]));
        return -RT_EINVAL;
    }

    if ((signed)(v[2] = spacemit_pmic_read(pmic, pmic_rtc->desc->alarm_h.reg)) < 0)
    {
        LOG_E("Failed to read alarm hour: %s", rt_strerror(v[2]));
        return -RT_EINVAL;
    }

    if ((signed)(v[3] = spacemit_pmic_read(pmic, pmic_rtc->desc->alarm_d.reg)) < 0)
    {
        LOG_E("Failed to read alarm day: %s", rt_strerror(v[3]));
        return -RT_EINVAL;
    }

    if ((signed)(v[4] = spacemit_pmic_read(pmic, pmic_rtc->desc->alarm_mo.reg)) < 0)
    {
        LOG_E("Failed to read alarm month: %s", rt_strerror(v[4]));
        return -RT_EINVAL;
    }

    if ((signed)(v[5] = spacemit_pmic_read(pmic, pmic_rtc->desc->alarm_y.reg)) < 0)
    {
        LOG_E("Failed to read alarm year: %s", rt_strerror(v[5]));
        return -RT_EINVAL;
    }

    /* 2000:1:1:0:0:0 */
    alarm->tm_sec = v[0] & pmic_rtc->desc->alarm_s.msk;
    alarm->tm_min = v[1] & pmic_rtc->desc->alarm_mi.msk;
    alarm->tm_hour = v[2] & pmic_rtc->desc->alarm_h.msk;
    alarm->tm_mday = (v[3] & pmic_rtc->desc->alarm_d.msk) + 1;
    alarm->tm_mon = (v[4] & pmic_rtc->desc->alarm_mo.msk);
    alarm->tm_year = (v[5] & pmic_rtc->desc->alarm_y.msk) + 100;

    if ((signed)(rtc_ctl.val = spacemit_pmic_read(pmic, pmic_rtc->desc->rtc_ctl.reg)) < 0)
    {
        LOG_E("Failed to read alarm second: %s", rt_strerror(rtc_ctl.val));
        return -RT_EINVAL;
    }

    alarm->enable = !!rtc_ctl.bits.alarm_en;

    return RT_EOK;
}

static rt_err_t spacemit_pmic_rtc_set_alarm(struct spacemit_pmic_rtc *pmic_rtc,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    union spacemit_pmic_rtc_ctl_desc rtc_ctl;
    struct spacemit_pmic *pmic = pmic_rtc->pmic;

    /* Disable the alrm function first */
    if ((signed)(rtc_ctl.val = spacemit_pmic_read(pmic, pmic_rtc->desc->rtc_ctl.reg)) < 0)
    {
        LOG_E("Failed to read rtc ctrl register: %s", rt_strerror(rtc_ctl.val));
        return -RT_EINVAL;
    }

    rtc_ctl.bits.alarm_en = 0;

    if ((err = spacemit_pmic_write_bit(pmic, pmic_rtc->desc->rtc_ctl.reg, 0xff, rtc_ctl.val)))
    {
        LOG_E("Failed to set rtc ctrl register: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    if ((err = spacemit_pmic_write_bit(pmic,
        pmic_rtc->desc->alarm_s.reg, pmic_rtc->desc->alarm_s.msk, alarm->tm_sec)))
    {
        LOG_E("Failed to update alrm second: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    if ((err = spacemit_pmic_write_bit(pmic,
        pmic_rtc->desc->alarm_mi.reg, pmic_rtc->desc->alarm_mi.msk, alarm->tm_min)))
    {
        LOG_E("Failed to update alarm minutes: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    if ((err = spacemit_pmic_write_bit(pmic,
        pmic_rtc->desc->alarm_h.reg, pmic_rtc->desc->alarm_h.msk, alarm->tm_hour)))
    {
        LOG_E("Failed to update alarm hour: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    if ((err = spacemit_pmic_write_bit(pmic,
        pmic_rtc->desc->alarm_d.reg, pmic_rtc->desc->alarm_d.msk, alarm->tm_mday - 1)))
    {
        LOG_E("Failed to update alarm day: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    if ((err = spacemit_pmic_write_bit(pmic,
        pmic_rtc->desc->alarm_mo.reg, pmic_rtc->desc->alarm_mo.msk, alarm->tm_mon)))
    {
        LOG_E("Failed to update alarm month: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    if ((err = spacemit_pmic_write_bit(pmic,
        pmic_rtc->desc->alarm_y.reg, pmic_rtc->desc->alarm_y.msk, alarm->tm_year - 100)))
    {
        LOG_E("Failed to update month: %s", rt_strerror(err));
        return -RT_EINVAL;
    }

    if (alarm->enable)
    {
        rtc_ctl.bits.alarm_en = 1;

        if ((err = spacemit_pmic_write_bit(pmic, pmic_rtc->desc->rtc_ctl.reg, 0xff, rtc_ctl.val)))
        {
            LOG_E("Failed to set rtc ctrl register: %s", rt_strerror(err));
            return -RT_EINVAL;
        }
    }

    return RT_EOK;
}

static rt_err_t spacemit_pmic_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct spacemit_pmic_rtc *pmic_rtc = raw_to_spacemit_pmic_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        err = spacemit_pmic_rtc_read_time(pmic_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        err = spacemit_pmic_rtc_set_time(pmic_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        err = spacemit_pmic_rtc_read_time(pmic_rtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        err = spacemit_pmic_rtc_set_time(pmic_rtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        err = spacemit_pmic_rtc_read_alarm(pmic_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = spacemit_pmic_rtc_set_alarm(pmic_rtc, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops spacemit_pmic_rtc_ops =
{
    .control = spacemit_pmic_rtc_control,
};
#endif

static void spacemit_pmic_rtc_isr(int irq, void *param)
{
    struct spacemit_pmic_rtc *pmic_rtc = param;

    rt_alarm_update(&pmic_rtc->parent, 1);
}

static rt_err_t spacemit_pmic_rtc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_pmic *pmic = pdev->priv;
    union spacemit_pmic_rtc_ctl_desc rtc_ctl;
    struct spacemit_pmic_rtc *pmic_rtc = rt_calloc(1, sizeof(*pmic_rtc));

    if (!pmic_rtc)
    {
        return -RT_ENOMEM;
    }

    pmic_rtc->pmic = pmic;
    pmic_rtc->desc = pdev->id->data;

    if ((pmic_rtc->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = pmic_rtc->irq;
        goto _fail;
    }

    /* Enable the rtc function */
    if ((signed)(rtc_ctl.val = spacemit_pmic_read(pmic, pmic_rtc->desc->rtc_ctl.reg)) < 0)
    {
        err = rtc_ctl.val;
        goto _fail;
    }

    /* Internal 32k clk */
    rtc_ctl.bits.rtc_clk_sel = 1;
    /* Enable rtc */
    rtc_ctl.bits.rtc_en = 1;
    /* RTC clk out enable */
    rtc_ctl.bits.out_32k_en = 1;
    /* Enable external crystal */
    rtc_ctl.bits.crystal_en = 1;

    if ((err = spacemit_pmic_update_bits(pmic, pmic_rtc->desc->rtc_ctl.reg, 0xff, rtc_ctl.val)))
    {
        goto _fail;
    }

    pmic_rtc->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    pmic_rtc->parent.ops = &spacemit_pmic_rtc_ops;
#else
    pmic_rtc->parent.control = spacemit_pmic_rtc_control;
#endif

    rtc_dev_set_name(&pmic_rtc->parent);
    dev_name = rt_dm_dev_get_name(&pmic_rtc->parent);
    rt_device_register(&pmic_rtc->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    rt_hw_interrupt_install(pmic_rtc->irq, spacemit_pmic_rtc_isr, pmic_rtc, "rtc-spacemit-pmic");
    rt_hw_interrupt_umask(pmic_rtc->irq);

    dev->user_data = pmic_rtc;

    return RT_EOK;
_fail:
    rt_free(pmic_rtc);

    return err;
}

static rt_err_t spacemit_pmic_rtc_remove(struct rt_platform_device *pdev)
{
    struct spacemit_pmic_rtc *pmic_rtc = pdev->parent.user_data;

    rt_hw_interrupt_mask(pmic_rtc->irq);
    rt_pic_detach_irq(pmic_rtc->irq, pmic_rtc);

    rt_device_unregister(&pmic_rtc->parent);

    rt_free(pmic_rtc);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_pmic_rtc_ofw_ids[] =
{
    { .compatible = "pmic,rtc,spm8821", .data = &spm8821_regdesc },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_pmic_rtc_driver =
{
    .name = "spacemit-pmic-rtc",
    .ids = spacemit_pmic_rtc_ofw_ids,

    .probe = spacemit_pmic_rtc_probe,
    .remove = spacemit_pmic_rtc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_pmic_rtc_driver);
