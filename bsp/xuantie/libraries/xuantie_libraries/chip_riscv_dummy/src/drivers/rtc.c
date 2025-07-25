/*
 *    Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */

/*******************************************************
 * @file       rtc.c
 * @brief      source file for rtc csi driver
 * @version    V1.0
 * @date       23. Sep 2020
 * ******************************************************/

#include <drv/rtc.h>
#include <drv/irq.h>
#include <time.h>

#define NORMAL_RTC_FREQ         (32768U)
#define REAL_RTC_FREQ           (soc_get_rtc_freq(0U))
#define RTC_WAIT_WRITED_10S     (10000U)

#define RTC_WAIT_IS_TIMEOUT(_time_ms_, _result_)      {        \
        do {                                                      \
            if (_time_ms_ >= RTC_WAIT_WRITED_10S) {            \
                _result_ = -1;                                    \
            }                                                     \
            mdelay(1U);                                           \
        } while(0);                                               \
    }

static uint32_t load_time = 0U;
static uint32_t int_number = 0U;
static uint32_t count = 0U;

extern int32_t clock_check_tm_ok(const struct tm *rtctime);
extern int32_t clock_update_basetime(const struct tm *rtctime);
extern time_t mktime(struct tm *tp);

/**
  \brief       Internal timeout interrupt process function
  \param[in]   rtc    handle rtc handle to operate
  \return      None
*/
void qx_rtc_irq_handler(void *arg)
{
    csi_rtc_t *rtc = (csi_rtc_t *)arg;
    uint32_t timecount = 0, ret = 0, intr_status = 0;

    ///< TODO：获取RTC中断的状态到intr_status

    do {
        ///< TODO：清除RTC的中断
        RTC_WAIT_IS_TIMEOUT(++timecount, ret);

        if (ret < 0) {
            break;
        }
    } while (intr_status);

    count++;

    if (count >= (int_number * (REAL_RTC_FREQ / NORMAL_RTC_FREQ))) {
        count = 0U;

        if (rtc->callback) {
            rtc->callback(rtc, rtc->arg);
        }
    }

}
/**
  \brief       Initialize RTC Interface. Initializes the resources needed for the RTC interface
  \param[in]   rtc    rtc handle to operate
  \param[in]   idx    rtc index
  \return      error code \ref csi_error_t
*/
csi_error_t csi_rtc_init(csi_rtc_t *rtc, uint32_t idx)
{
    CSI_PARAM_CHK(rtc, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    if (0 == target_get(DEV_QX_RTC_TAG, idx, &rtc->dev)) {
        ///< TODO：相关寄存器复位清零
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}
/**
  \brief       De-initialize RTC Interface. stops operation and releases the software resources used by the interface
  \param[in]   rtc    rtc handle to operate
  \return      None
*/
void csi_rtc_uninit(csi_rtc_t *rtc)
{
    CSI_PARAM_CHK_NORETVAL(rtc);

    ///< TODO：相关寄存器复位清零
}

/**
  \brief       Set system date
  \param[in]   rtc        handle rtc handle to operate
  \param[in]   rtctime    pointer to rtc time
  \return      error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_time(csi_rtc_t *rtc, const csi_rtc_time_t *rtctime)
{
    CSI_PARAM_CHK(rtc, CSI_ERROR);
    CSI_PARAM_CHK(rtctime, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    int32_t load_sec;

    do {
        ret = (csi_error_t)clock_check_tm_ok((const struct tm *)rtctime);

        if (ret < CSI_OK) {
            break;
        }

        load_sec = clock_update_basetime((const struct tm *)rtctime);

        if (load_sec <= 0) {        ///< Error returned when total seconds overflow is negative
            ret = CSI_ERROR;
            break;
        }

        load_time = (uint32_t)load_sec;
        ///< TODO：用load_sec设置RTC的加载值寄存器，该处操作有一段等待同步时间

        if (ret < CSI_OK) {
            break;
        }

        ///< TODO：使能计数器

    } while (0);

    return ret;
}
/**
  \brief       Set system date but no wait
  \param[in]   rtc        rtc handle to operate
  \param[in]   rtctime    pointer to rtc time
  \return      error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_time_no_wait(csi_rtc_t *rtc, const csi_rtc_time_t *rtctime)
{
    CSI_PARAM_CHK(rtc, CSI_ERROR);
    CSI_PARAM_CHK(rtctime, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    int32_t load_sec;

    do {

        ret = (csi_error_t)clock_check_tm_ok((const struct tm *)rtctime);

        if (ret < CSI_OK) {
            break;
        }

        load_sec = clock_update_basetime((const struct tm *)rtctime);

        if (load_sec <= 0) {        ///< Error returned when total seconds overflow is negative
            ret = CSI_ERROR;
            break;
        }

        ///< TODO：用load_sec设置RTC的加载值寄存器

        ///< TODO：使能计数器

    } while (0);

    return ret;
}
/**
  \brief       Get system date
  \param[in]   rtc        handle rtc handle to operate
  \param[out]  rtctime    pointer to rtc time
  \return      error code \ref csi_error_t
*/
csi_error_t csi_rtc_get_time(csi_rtc_t *rtc, csi_rtc_time_t *rtctime)
{
    uint32_t cur_time = 0;
    time_t time;

    CSI_PARAM_CHK(rtc, CSI_ERROR);
    CSI_PARAM_CHK(rtctime, CSI_ERROR);

    ///< TODO：获取当前时间到cur_time
    time = (time_t)(((cur_time - load_time) / (REAL_RTC_FREQ / NORMAL_RTC_FREQ)) + load_time);
    gmtime_r(&time, (struct tm *)rtctime);

    return CSI_OK;
}

/**
  \brief       Get alarm remaining time
  \param[in]   rtc    rtc handle to operate
  \return      the remaining time(s)
*/
uint32_t csi_rtc_get_alarm_remaining_time(csi_rtc_t *rtc)
{
    CSI_PARAM_CHK(rtc, 0U);

    ///< 返回RTC剩余多长时间产生闹钟中断
    return (int_number - (count / (REAL_RTC_FREQ / NORMAL_RTC_FREQ)));
}

/**
  \brief       Config RTC alarm ture timer
  \param[in]   rtc         handle rtc handle to operate
  \param[in]   rtctime     time(s) to wake up
  \param[in]   callback    callback function
  \param[in]   arg         callback's param
  \return      error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_alarm(csi_rtc_t *rtc, const csi_rtc_time_t *rtctime, void *callback, void *arg)
{
    CSI_PARAM_CHK(rtc, CSI_ERROR);
    CSI_PARAM_CHK(rtctime, CSI_ERROR);
    csi_error_t ret = (csi_error_t)clock_check_tm_ok((const struct tm *)rtctime);
    csi_rtc_time_t current_time;

    if (CSI_OK == ret) {
        rtc->callback = callback;
        rtc->arg = arg;
        ///< 注册RTC的中断服务函数，使能中断控制器中对应的中断
        csi_irq_attach((uint32_t)rtc->dev.irq_num, &qx_rtc_irq_handler, &rtc->dev);
        csi_irq_enable((uint32_t)rtc->dev.irq_num);

        csi_rtc_get_time(rtc, &current_time);            ///< get current time
        count = 0U;
        int_number = ((uint32_t)mktime((struct tm *)rtctime) - (uint32_t)mktime((struct tm *)&current_time));
        ///< TODO：使能RTC的中断
    }

    return ret;
}

/**
  \brief       Cancel the rtc alarm
  \param[in]   rtc    rtc handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_rtc_cancel_alarm(csi_rtc_t *rtc)
{
    CSI_PARAM_CHK(rtc, CSI_ERROR);

    rtc->callback = NULL;
    rtc->arg = NULL;

    ///< TODO：禁止中断

    ///< 关闭中断控制器中对应的使能，注销RTC的中断服务函数
    csi_irq_disable((uint32_t)rtc->dev.irq_num);
    csi_irq_detach((uint32_t)rtc->dev.irq_num);

    return CSI_OK;
}

/**
  \brief       Judge rtc is working
  \param[in]   rtc    handle rtc handle to operate
  \return      state of work
               ture - rtc is running
               false -rtc is not running
*/
bool csi_rtc_is_running(csi_rtc_t *rtc)
{
    CSI_PARAM_CHK(rtc, false);

    bool status = 0;

    ///< TODO：获取RTC运行的状态

    return status;
}

#ifdef CONFIG_PM
csi_error_t csi_rtc_enable_pm(csi_rtc_t *rtc)
{
    return CSI_UNSUPPORTED;
}

void csi_rtc_disable_pm(csi_rtc_t *rtc)
{
    return;
}
#endif
