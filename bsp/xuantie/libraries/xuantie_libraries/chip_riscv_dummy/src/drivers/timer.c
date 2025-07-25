/*
 *  Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */

/*******************************************************
 * @file    dw_timer.c
 * @brief   source file for timer csi driver
 * @version V1.0
 * @date    28. Apr 2020
 * ******************************************************/

#include <csi_config.h>
#include <drv/timer.h>
#include <drv/irq.h>
#include "dw_timer_ll.h"

/**
  \brief       Timer interrupt handling function
  \param[in]   arg    Callback function member variables
  \return      None
*/
void dw_timer_irq_handler(void *arg)
{
    csi_timer_t *timer = (csi_timer_t *)arg;
    dw_timer_regs_t *timer_base = (dw_timer_regs_t *)timer->dev.reg_base;

    if (dw_timer_get_int_status(timer_base)) {
        if (timer->callback) {
            timer->callback(timer, timer->arg);
        }

        dw_timer_clear_irq(timer_base);
    }
}
#if CONFIG_SUPPORT_NMI_DEMO
void timer_clear_irq()
{
    dw_timer_clear_irq((dw_timer_regs_t*)DW_TIMER4_BASE);
}
#endif
/**
  \brief       Initialize TIMER Interface. 1. Initializes the resources needed for the TIMER interface 2.registers callback function
  \param[in]   timer    handle timer handle to operate
  \param[in]   idx      timer index
  \return      error code \ref csi_error_t
*/
csi_error_t csi_timer_init(csi_timer_t *timer, uint32_t idx)
{
    CSI_PARAM_CHK(timer, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    dw_timer_regs_t *timer_base = NULL;

    if (0 == target_get(DEV_DW_TIMER_TAG, idx, &timer->dev)) {
        timer_base = (dw_timer_regs_t *)HANDLE_REG_BASE(timer);
        memset((void *)timer_base, 0, sizeof(dw_timer_regs_t));

    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
/**
  \brief       De-initialize TIMER Interface. stops operation and releases the software resources used by the interface
  \param[in]   timer    handle timer handle to operate
  \return      None
*/
void csi_timer_uninit(csi_timer_t *timer)
{
    CSI_PARAM_CHK_NORETVAL(timer);
    dw_timer_regs_t *timer_base = (dw_timer_regs_t *)HANDLE_REG_BASE(timer);

    memset((void *)timer_base, 0, sizeof(dw_timer_regs_t));
}
/**
  \brief       Start timer
  \param[in]   timer         handle timer handle to operate
  \param[in]   timeout_us    the timeout for timer
  \return      error code \ref csi_error_t
*/
csi_error_t csi_timer_start(csi_timer_t *timer, uint32_t timeout_us)
{
    CSI_PARAM_CHK(timer, CSI_ERROR);
    CSI_PARAM_CHK(timeout_us, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    dw_timer_regs_t *timer_base = (dw_timer_regs_t *)HANDLE_REG_BASE(timer);
    uint32_t tmp_load = timeout_us * (soc_get_timer_freq((uint32_t)timer->dev.idx) / 1000000U);

    dw_timer_set_mode_load(timer_base);
    dw_timer_write_load(timer_base, tmp_load);

    dw_timer_set_disable(timer_base);
    dw_timer_set_enable(timer_base);
    dw_timer_set_unmask(timer_base);

    return ret;
}
/**
  \brief       Stop timer
  \param[in]   timer    handle timer handle to operate
  \return      None
*/
void csi_timer_stop(csi_timer_t *timer)
{
    CSI_PARAM_CHK_NORETVAL(timer);

    dw_timer_regs_t *timer_base;
    timer_base = (dw_timer_regs_t *)HANDLE_REG_BASE(timer);

    dw_timer_set_mask(timer_base);
    dw_timer_set_disable(timer_base);
}
/**
  \brief       Get timer remaining value
  \param[in]   timer    handle timer handle to operate
  \return      the remaining value
*/
uint32_t csi_timer_get_remaining_value(csi_timer_t *timer)
{
    CSI_PARAM_CHK(timer, 0U);

    dw_timer_regs_t *timer_base;
    timer_base = (dw_timer_regs_t *)HANDLE_REG_BASE(timer);
    return dw_timer_get_current(timer_base);
}
/**
  \brief       Get timer load value
  \param[in]   timer    handle timer handle to operate
  \return      the load value
*/
uint32_t csi_timer_get_load_value(csi_timer_t *timer)
{
    CSI_PARAM_CHK(timer, 0U);

    dw_timer_regs_t *timer_base = (dw_timer_regs_t *)HANDLE_REG_BASE(timer);

    return (dw_timer_read_load(timer_base));
}
/**
  \brief       Check timer is running
  \param[in]   timer    handle timer handle to operate
  \return      true->running, false->stopped
*/
bool csi_timer_is_running(csi_timer_t *timer)
{
    CSI_PARAM_CHK(timer, false);

    dw_timer_regs_t *timer_base = (dw_timer_regs_t *)HANDLE_REG_BASE(timer);

    return (dw_timer_get_enable(timer_base) ? true : false);
}

/**
  \brief       Attach the callback handler to timer
  \param[in]   timer       operate handle.
  \param[in]   callback    callback function
  \param[in]   arg         callback's param
  \return      error code \ref csi_error_t
*/
csi_error_t csi_timer_attach_callback(csi_timer_t *timer, void *callback, void *arg)
{
    CSI_PARAM_CHK(timer, CSI_ERROR);

    timer->callback = callback;
    timer->arg = arg;
    csi_irq_attach((uint32_t)timer->dev.irq_num, &dw_timer_irq_handler, &timer->dev);
    csi_irq_enable((uint32_t)timer->dev.irq_num);

    return CSI_OK;
}

/**
  \brief       Detach the callback handler
  \param[in]   timer    operate handle.
*/
void csi_timer_detach_callback(csi_timer_t *timer)
{
    CSI_PARAM_CHK_NORETVAL(timer);

    timer->callback = NULL;
    timer->arg = NULL;
    csi_irq_disable((uint32_t)timer->dev.irq_num);
    csi_irq_detach((uint32_t)timer->dev.irq_num);
}

#ifdef CONFIG_PM
csi_error_t dw_timer_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;

    switch (action) {
    case PM_DEV_SUSPEND:
        csi_pm_dev_save_regs(pm_dev->reten_mem, (uint32_t *)dev->reg_base, 1U);
        csi_pm_dev_save_regs(pm_dev->reten_mem + 1, (uint32_t *)(dev->reg_base + 8U), 1U);
        break;

    case PM_DEV_RESUME:
        csi_pm_dev_restore_regs(pm_dev->reten_mem, (uint32_t *)dev->reg_base, 1U);
        csi_pm_dev_restore_regs(pm_dev->reten_mem + 1, (uint32_t *)(dev->reg_base + 8U), 1U);
        break;

    default:
        ret = CSI_ERROR;
        break;
    }

    return ret;
}

csi_error_t csi_timer_enable_pm(csi_timer_t *timer)
{
    return csi_pm_dev_register(&timer->dev, dw_timer_pm_action, 8U, 0U);
}

void csi_timer_disable_pm(csi_timer_t *timer)
{
    csi_pm_dev_unregister(&timer->dev);
}
#endif

