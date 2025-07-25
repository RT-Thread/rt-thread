/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "wdt.i6300esb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define I6300ESB_REG_BAR        0

/* PCI configuration registers */
#define ESB_CONFIG_PCI_REG      0x60    /* Config register */
#define ESB_LOCK_PCI_REG        0x68    /* WDT lock register */

/* Memory mapped registers */
#define ESB_TIMER1_REG          0x00    /* Timer1 value after each reset */
#define ESB_TIMER2_REG          0x04    /* Timer2 value after each reset */
#define ESB_GINTSR_REG          0x08    /* General Interrupt Status Reg */
#define ESB_RELOAD_REG          0x0c    /* Reload register */

/* Lock register bits */
#define ESB_WDT_FUNC            (0x01 << 2) /* Watchdog functionality */
#define ESB_WDT_ENABLE          (0x01 << 1) /* Enable WDT */
#define ESB_WDT_LOCK            (0x01 << 0) /* Lock (nowayout) */

/* Config register bits */
#define ESB_WDT_REBOOT          (0x01 << 5) /* Enable reboot on timeout */
#define ESB_WDT_FREQ            (0x01 << 2) /* Decrement frequency */
#define ESB_WDT_INTTYPE         (0x03 << 0) /* Interrupt type on timer1 timeout */

/* Reload register bits */
#define ESB_WDT_TIMEOUT         (0x01 << 9) /* Watchdog timed out */
#define ESB_WDT_RELOAD          (0x01 << 8) /* prevent timeout */

/* Magic constants */
#define ESB_UNLOCK1             0x80    /* Step 1 to unlock reset registers */
#define ESB_UNLOCK2             0x86    /* Step 2 to unlock reset registers */

/* 30 sec default heartbeat (1 < heartbeat < 2*1023) */
#define ESB_HEARTBEAT_MIN       1
#define ESB_HEARTBEAT_MAX       2046
#define ESB_HEARTBEAT_DEFAULT   30

struct i6300esb_wdt
{
    rt_watchdog_t parent;

    void *regs;
    rt_uint32_t timeout;
    struct rt_pci_device *pdev;
};

#define raw_to_i6300esb_wdt(raw) rt_container_of(raw, struct i6300esb_wdt, parent)

/*
 * Prepare for reloading the timer by unlocking the proper registers.
 * This is performed by first writing 0x80 followed by 0x86 to the
 * reload register. After this the appropriate registers can be written
 * to once before they need to be unlocked again.
 */
rt_inline void i6300esb_wdt_unlock_registers(struct i6300esb_wdt *esb)
{
    HWREG16(esb->regs + ESB_RELOAD_REG) = ESB_UNLOCK1;
    HWREG16(esb->regs + ESB_RELOAD_REG) = ESB_UNLOCK2;
}

static rt_uint32_t i6300esb_timer_start(struct i6300esb_wdt *esb)
{
    i6300esb_wdt_unlock_registers(esb);
    HWREG16(esb->regs + ESB_RELOAD_REG) = ESB_WDT_RELOAD;

    rt_pci_write_config_u8(esb->pdev, ESB_LOCK_PCI_REG, ESB_WDT_ENABLE);

    return RT_EOK;
}

static rt_uint32_t i6300esb_timer_stop(struct i6300esb_wdt *esb)
{
    rt_uint8_t val;

    /* First, reset timers as suggested by the docs */
    i6300esb_wdt_unlock_registers(esb);
    HWREG16(esb->regs + ESB_RELOAD_REG) = ESB_WDT_RELOAD;

    /* Then disable the WDT */
    rt_pci_write_config_u8(esb->pdev, ESB_LOCK_PCI_REG, 0x0);
    rt_pci_read_config_u8(esb->pdev, ESB_LOCK_PCI_REG, &val);

    /* Returns 0 if the timer was disabled, non-zero otherwise */
    return val & ESB_WDT_ENABLE;
}

static rt_err_t esb_timer_keepalive(struct i6300esb_wdt *esb)
{
    i6300esb_wdt_unlock_registers(esb);
    HWREG16(esb->regs + ESB_RELOAD_REG) = ESB_WDT_RELOAD;

    return RT_EOK;
}

static rt_err_t i6300esb_timer_set_heartbeat(struct i6300esb_wdt *esb, rt_uint32_t time)
{
    rt_uint32_t val;

    /*
     * We shift by 9, so if we are passed a value of 1 sec,
     * val will be 1 << 9 = 512, then write that to two
     * timers => 2 * 512 = 1024 (which is decremented at 1KHz)
     */
    val = time << 9;

    /* Write timer 1 */
    i6300esb_wdt_unlock_registers(esb);
    HWREG32(esb->regs + ESB_TIMER1_REG) = val;

    /* Write timer 2 */
    i6300esb_wdt_unlock_registers(esb);
    HWREG32(esb->regs + ESB_TIMER2_REG) = val;

    /* Reload */
    i6300esb_wdt_unlock_registers(esb);
    HWREG16(esb->regs + ESB_RELOAD_REG) = ESB_WDT_RELOAD;

    esb->timeout = time;

    return RT_EOK;
}

static rt_err_t i6300esb_wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t i6300esb_wdt_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct i6300esb_wdt *esb = raw_to_i6300esb_wdt(wdt);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)args = esb->timeout;
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        err = i6300esb_timer_set_heartbeat(esb, *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        err = esb_timer_keepalive(esb);
        break;

    case RT_DEVICE_CTRL_WDT_START:
        err = i6300esb_timer_start(esb);
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        err = i6300esb_timer_stop(esb);
        break;

    default:
        err = -RT_EINVAL;
    }

    return err;
}

static const struct rt_watchdog_ops i6300esb_wdt_ops =
{
    .init = i6300esb_wdt_init,
    .control = i6300esb_wdt_control,
};

static rt_err_t i6300esb_wdt_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    rt_uint8_t val1;
    rt_uint16_t val2;
    const char *dev_name;
    struct i6300esb_wdt *esb = rt_calloc(1, sizeof(*esb));

    if (!esb)
    {
        return -RT_ENOMEM;
    }

    esb->regs = rt_pci_iomap(pdev, I6300ESB_REG_BAR);

    if (!esb->regs)
    {
        err = -RT_EIO;

        goto _fail;
    }

    /*
     * Config register:
     * Bit    5 : 0 = Enable WDT_OUTPUT
     * Bit    2 : 0 = set the timer frequency to the PCI clock
     * divided by 2^15 (approx 1KHz).
     * Bits 1:0 : 11 = WDT_INT_TYPE Disabled.
     * The watchdog has two timers, it can be setup so that the expiry of timer1
     * results in an interrupt and the expiry of timer2 results in a reboot.
     * We set it to not generate any interrupts as there is not much
     * we can do with it right now.
     */
    rt_pci_write_config_u16(pdev, ESB_CONFIG_PCI_REG, 0x0003);

    /* Check that the WDT isn't already locked */
    rt_pci_read_config_u8(pdev, ESB_LOCK_PCI_REG, &val1);
    if (val1 & ESB_WDT_LOCK)
    {
        LOG_W("Nowayout already set");
    }

    /* Set the timer to watchdog mode and disable it for now */
    rt_pci_write_config_u8(pdev, ESB_LOCK_PCI_REG, 0x00);

    /* Check if the watchdog was previously triggered */
    i6300esb_wdt_unlock_registers(esb);
    val2 = HWREG16(esb->regs + ESB_RELOAD_REG);
    if (val2 & ESB_WDT_TIMEOUT)
    {
        LOG_D("Card previously reset the CPU");
    }

    /* Reset WDT_TIMEOUT flag and timers */
    i6300esb_wdt_unlock_registers(esb);
    HWREG16(esb->regs + ESB_RELOAD_REG) = ESB_WDT_TIMEOUT | ESB_WDT_RELOAD;

    /* And set the correct timeout value */
    i6300esb_timer_set_heartbeat(esb, ESB_HEARTBEAT_DEFAULT);

    pdev->parent.user_data = esb;

    esb->pdev = pdev;
    esb->parent.ops = &i6300esb_wdt_ops;

    rt_dm_dev_set_name_auto(&esb->parent.parent, "wdt");
    dev_name = rt_dm_dev_get_name(&esb->parent.parent);
    rt_hw_watchdog_register(&esb->parent, dev_name, 0, esb);

    return RT_EOK;

_fail:
    if (esb->regs)
    {
        rt_iounmap(esb->regs);
    }

    rt_free(esb);

    return err;
}

static rt_err_t i6300esb_wdt_remove(struct rt_pci_device *pdev)
{
    struct i6300esb_wdt *esb = pdev->parent.user_data;

    i6300esb_timer_stop(esb);

    rt_device_unregister(&esb->parent.parent);

    rt_iounmap(esb->regs);
    rt_free(esb);

    return RT_EOK;
}

static const struct rt_pci_device_id i6300esb_wdt_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_INTEL, 0x25ab), },
    { /* sentinel */ }
};

static struct rt_pci_driver i6300esb_wdt_driver =
{
    .name = "i6300esb-wdt",

    .ids = i6300esb_wdt_pci_ids,
    .probe = i6300esb_wdt_probe,
    .remove = i6300esb_wdt_remove,
};
RT_PCI_DRIVER_EXPORT(i6300esb_wdt_driver);
