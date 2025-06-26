/*
 *  Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */

/*******************************************************
 * @file       dw_wdt.c
 * @brief      source file for wdt csi driver
 * @version    V1.0
 * @date       23. Sep 2020
 * ******************************************************/

#include <drv/wdt.h>
#include <drv/irq.h>

void dw_wdt_irq_handler(void *arg)
{

    ///< TODO：获取WDT的中断状态
    ///< TODO：根据中断状态执行用户回调函数

}

/**
  \brief       Initialize WDT Interface. Initializes the resources needed for the WDT interface
  \param[in]   wdt    wdt handle to operate
  \param[in]   idx    wdt index
  \return      error code \ref csi_error_t
*/
csi_error_t csi_wdt_init(csi_wdt_t *wdt, uint32_t idx)
{
    CSI_PARAM_CHK(wdt, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    if (0 == target_get(DEV_DW_WDT_TAG, idx, &wdt->dev)) {

        ///< TODO：复位WDT的控制寄存器
        ///< TODO：复位WDT的超时时间范围寄存器
        ///< TODO：复位重启WDT计数器寄存器

    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
/**
  \brief       De-initialize WDT Interface. stops operation and releases the software resources used by the interface
  \param[in]   wdt    handle to operate
  \return      None
*/
void csi_wdt_uninit(csi_wdt_t *wdt)
{
    CSI_PARAM_CHK_NORETVAL(wdt);

    ///< TODO：复位WDT的控制寄存器
    ///< TODO：复位WDT的超时时间范围寄存器
    ///< TODO：复位重启WDT计数器寄存器

}
/**
  \brief       Set the WDT value
  \param[in]   wdt    handle to operate
  \param[in]   ms     the timeout value(ms)
  \return      error code \ref csi_error_t
*/
csi_error_t csi_wdt_set_timeout(csi_wdt_t *wdt, uint32_t ms)
{
    CSI_PARAM_CHK(wdt, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< TODO：关闭WDT

    ///< TODO：设置超时时间
    ///< TODO：打开WDT
    ///< TODO：重启WDT计数器

    return ret;
}
/**
  \brief       Start the WDT
  \param[in]   wdt    handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_wdt_start(csi_wdt_t *wdt)
{
    CSI_PARAM_CHK(wdt, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< TODO：打开WDT
    ///< TODO：重启WDT计数器

    return ret;
}
/**
  \brief       Stop the WDT
  \param[in]   wdt    handle to operate
  \return      None
*/
void csi_wdt_stop(csi_wdt_t *wdt)
{
    CSI_PARAM_CHK_NORETVAL(wdt);

    ///< TODO：关闭WDT
}
/**
  \brief       Feed the WDT
  \param[in]   wdt    handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_wdt_feed(csi_wdt_t *wdt)
{
    CSI_PARAM_CHK(wdt, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< TODO：喂狗

    return ret;
}

/**
  \brief       Get the remaining time to timeout
  \param[in]   wdt    handle to operate
  \return      tne remaining time of wdt(ms)
*/
uint32_t csi_wdt_get_remaining_time(csi_wdt_t *wdt)
{
    CSI_PARAM_CHK(wdt, 0U);
    uint32_t time = 0U;

    ///< TODO：获取前剩余的时间time，单位为ms

    return time;
}

/**
  \brief       Check wdt is running
  \param[in]   wdt    handle wdt handle to operate
  \return      true->running, false->stopped
*/
bool csi_wdt_is_running(csi_wdt_t *wdt)
{
    CSI_PARAM_CHK(wdt, false);
    uint32_t status = 0U;

    ///< TODO：获取WDT是否使能的状态status

    return status;
}

/**
  \brief       Attach the callback handler to wdt
  \param[in]   wdt         operate handle
  \param[in]   callback    callback function
  \param[in]   arg         callback's param
  \return      error code \ref csi_error_t
*/
csi_error_t csi_wdt_attach_callback(csi_wdt_t *wdt, void *callback, void *arg)
{
    CSI_PARAM_CHK(wdt, CSI_ERROR);

    wdt->callback = callback;
    wdt->arg = arg;
    ///<注册WDT中断服务函数，使能中断控制器对应的中断
    csi_irq_attach((uint32_t)wdt->dev.irq_num, &dw_wdt_irq_handler, &wdt->dev);
    csi_irq_enable((uint32_t)wdt->dev.irq_num);

    ///< TODO：设置WDT超时时产生系统复位

    return CSI_OK;
}

/**
  \brief       Detach the callback handler
  \param[in]   wdt    operate handle
  \return      None
*/
void csi_wdt_detach_callback(csi_wdt_t *wdt)
{
    CSI_PARAM_CHK_NORETVAL(wdt);

    wdt->callback = NULL;
    wdt->arg = NULL;
    ///<关闭中断控制器对应的中断，注销WDT中断服务函数
    csi_irq_disable((uint32_t)wdt->dev.irq_num);
    csi_irq_detach((uint32_t)wdt->dev.irq_num);

    ///< TODO：复位WDT超时时产生系统复位的功能

}

#ifdef CONFIG_PM
csi_error_t dw_wdt_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;

    switch (action) {
        case PM_DEV_SUSPEND:
            ///< TODO：恢复WDT寄存器
            break;

        case PM_DEV_RESUME:
            ///< TODO：保存WDT寄存器
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_wdt_enable_pm(csi_wdt_t *wdt)
{
    ///< TODO：注册WDT低功耗处理函数dw_wdt_pm_action
}

void csi_wdt_disable_pm(csi_wdt_t *wdt)
{
    csi_pm_dev_unregister(&wdt->dev);
}
#endif

