/*
 *  Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */

/*******************************************************
 * @file       pwm.c
 * @brief      source file for pwm csi driver
 * @version    V2.0
 * @date       23. Sep 2020
 * ******************************************************/

#include <drv/pwm.h>
#include <drv/irq.h>

/**
  \brief       PWM interrupt handling function
  \param[in]   arg    Callback function member variables
  \return      None
*/
void wj_pwm_irq_handler(void *arg)
{

    ///< TODO：判断中断是否发生
    ///< TODO：如果发生了则清除中断
    ///< TODO：如果发生处理中断

}

/**
  \brief       Initialize PWM Interface. 1. Initializes the resources needed for the PWM interface
  \param[in]   pwm    pwm handle to operate
  \param[in]   idx    pwm idx
  \return      error code
*/
csi_error_t csi_pwm_init(csi_pwm_t *pwm, uint32_t idx)
{
    CSI_PARAM_CHK(pwm, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< 初始化PWM控制器

    ///< 获取中断号、基地址等相关信息
    if (0 == target_get(DEV_WJ_PWM_TAG, idx, &pwm->dev)) {

        ///< TODO：把PWM相关寄存器复位清零

    } else {
        ret = CSI_ERROR;
    }

    return ret;
}

/**
  \brief       De-initialize PWM Interface. stops operation and releases the software resources used by the interface
  \param[in]   pwm    pwm handle to operate
  \return      None
*/
void csi_pwm_uninit(csi_pwm_t *pwm)
{
    CSI_PARAM_CHK_NORETVAL(pwm);

    ///< TODO：把PWM相关寄存器复位清零

}

/**
  \brief       Config pwm out mode
  \param[in]   pwm               pwm handle to operate
  \param[in]   channel           channel num
  \param[in]   period_us         the PWM period in us
  \param[in]   pulse_width_us    the PMW pulse width in us
  \param[in]   polarity          the PWM polarity \ref csi_pwm_polarity_t
  \return      error code
*/
csi_error_t csi_pwm_out_config(csi_pwm_t *pwm,
                               uint32_t  channel,
                               uint32_t period_us,
                               uint32_t pulse_width_us,
                               csi_pwm_polarity_t polarity)
{
    CSI_PARAM_CHK(pwm, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< TODO：检查参数channel的正确性

    ///< TODO：设置PWM通道的模式
    ///< TODO：根据period_us、pulse_width_us设置PWM的占空比

    return ret;
}

/**
  \brief       Start generate pwm signal
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      error code
*/
csi_error_t csi_pwm_out_start(csi_pwm_t *pwm, uint32_t channel)
{
    CSI_PARAM_CHK(pwm, CSI_ERROR);

    ///< TODO：打开输出使能

    return CSI_OK;
}

/**
  \brief       Stop generate pwm signal
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      None
*/
void csi_pwm_out_stop(csi_pwm_t *pwm, uint32_t channel)
{
    CSI_PARAM_CHK_NORETVAL(pwm);

    ///< TODO：关闭输出
}

/**
  \brief       Config pwm capture mode
  \param[in]   pwm         pwm handle to operate
  \param[in]   channel     channel num
  \param[in]   polarity    pwm capture polarity \ref csi_pwm_capture_polarity_t
  \param[in]   count       pwm capture polarity count
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_capture_config(csi_pwm_t *pwm,
                                   uint32_t channel,
                                   csi_pwm_capture_polarity_t polarity,
                                   uint32_t count)
{
    CSI_PARAM_CHK(pwm, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< TODO：检查参数channel的正确性

    if (CSI_OK == ret) {
        switch (polarity) {
            case PWM_CAPTURE_POLARITY_POSEDGE:
                ///< TODO：设置PWM捕获的极性为posedge edge
                break;

            case PWM_CAPTURE_POLARITY_NEGEDGE:
                ///< TODO：设置PWM捕获的极性为negedge edge
                break;

            case PWM_CAPTURE_POLARITY_BOTHEDGE:
                ///< TODO：设置PWM捕获的极性为both edge
                break;

            default:
                ret = CSI_ERROR;
                break;
        }

        ///< TODO：配置捕获次数

        ///< TODO：配置捕获模式

        ///< TODO：启用捕获中断
    }

    return ret;
}

/**
  \brief       Start pwm capture
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_capture_start(csi_pwm_t *pwm, uint32_t channel)
{
    CSI_PARAM_CHK(pwm, CSI_ERROR);

    ///< TODO：关闭输出使能

    ///< TODO：打开输入捕获使能

    ///< TODO：获取捕获次数

    return CSI_OK;
}

/**
  \brief       Stop pwm capture
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      None
*/
void csi_pwm_capture_stop(csi_pwm_t *pwm, uint32_t channel)
{
    CSI_PARAM_CHK_NORETVAL(pwm);

    ///< TODO：关闭PWM输入捕获
    ///< TODO：关闭PWM捕获中断
}
/**
  \brief       Attach pwm callback
  \param[in]   pwm         pwm handle to operate
  \param[in]   callback    callback func
  \param[in]   arg         user param passed to callback
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_attach_callback(csi_pwm_t *pwm, void *callback, void *arg)
{
    CSI_PARAM_CHK(pwm, CSI_ERROR);

    pwm->callback = callback;
    pwm->arg = arg;

    ///< 注册PWM的中断服务函数和使能中断控制器对应的中断
    csi_irq_attach((uint32_t)pwm->dev.irq_num, &wj_pwm_irq_handler, &pwm->dev);
    csi_irq_enable((uint32_t)pwm->dev.irq_num);

    return CSI_OK;
}

/**
  \brief       Detach pwm callback
  \param[in]   pwm    pwm handle to operate
  \return      None
*/
void csi_pwm_detach_callback(csi_pwm_t *pwm)
{
    CSI_PARAM_CHK_NORETVAL(pwm);

    pwm->callback = NULL;
    pwm->arg = NULL;

    ///< 禁止中断控制器对应的中断，注销PWM的中断服务函数
    csi_irq_disable((uint32_t)pwm->dev.irq_num);
    csi_irq_detach((uint32_t)pwm->dev.irq_num);
}

#ifdef CONFIG_PM
csi_error_t wj_pwm_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;

    switch (action) {
        case PM_DEV_SUSPEND:
            ///< TODO：恢复PWM寄存器
            break;

        case PM_DEV_RESUME:
            ///< TODO：保存PWM寄存器
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_pwm_enable_pm(csi_pwm_t *pwm)
{
    ///< TODO：注册PWM低功耗处理函数wj_pwm_pm_action
}

void csi_pwm_disable_pm(csi_pwm_t *pwm)
{
    csi_pm_dev_unregister(&pwm->dev);
}
#endif
