/**************************************************************************//**
*
* @copyright (C) 2026 Novosense Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2026-5-7        Alex-J           First version
*
******************************************************************************/

#ifndef __DRV_ECAP_H__
#define __DRV_ECAP_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ECAP_DEVICE_NAME_MAX        8U

/*
 * control command
 */
#define ECAP_CMD_ENABLE                 (0x01)
#define ECAP_CMD_DISABLE                (0x02)
#define ECAP_CMD_REARM                  (0x03)
#define ECAP_CMD_GET_LAST_CAPTURE       (0x04)
#define ECAP_CMD_SET_CALLBACK           (0x05)
#define ECAP_CMD_CLEAR_FLAGS            (0x06)
#define ECAP_CMD_ENABLE_IRQ             (0x07)
#define ECAP_CMD_DISABLE_IRQ            (0x08)

/*
 * ECAP capture status
 */
#define ECAP_STATUS_IDLE            (0x00U)
#define ECAP_STATUS_DONE            (0x01U)
#define ECAP_STATUS_OVERFLOW        (0x02U)
#define ECAP_STATUS_CAPTURE         (0x04U)
#define ECAP_STATUS_TIMEOUT         (0x05U)

/*
 * Capture result.
 *
 * cap1~cap4 对应 ECAP CEVT1~CEVT4 的捕获值。
 * period_high / period_low 可根据当前边沿配置计算。
 */
struct rt_ecap_capture
{
    rt_uint32_t cap1;
    rt_uint32_t cap2;
    rt_uint32_t cap3;
    rt_uint32_t cap4;

    rt_uint32_t period_low;
    rt_uint32_t period_high;
    rt_uint32_t period_total;

    rt_uint32_t status;
};

typedef void (*rt_ecap_rx_callback_t)(struct rt_ecap_capture *capture, void *user_data);

struct rt_ecap_callback
{
    rt_ecap_rx_callback_t callback;
    void *user_data;
};

/*
 * Static ECAP hardware configuration.
 */
struct rt_ecap_config
{
    const char *name;

    ECAP_TypeDef *instance;
    IRQn_Type     irq_type;

    rt_uint32_t input_xbar;
    rt_uint32_t ecap_input;
    rt_uint32_t input_source;

    GPIO_TypeDef *gpio_port;
    GPIO_PinNum gpio_pin;
    GPIO_AltFunc gpio_mux;
    void (*irq_handler)(void);
};

/*
 * ECAP device object.
 */
struct rt_ecap_device
{
    struct rt_device parent;

    const struct rt_ecap_config *config;

    struct rt_mutex lock;
    struct rt_semaphore rx_sem;

    volatile struct rt_ecap_capture last_capture;

    rt_ecap_rx_callback_t rx_callback;
    void *rx_user_data;

    rt_uint8_t opened;
};

int rt_hw_ecap_init(void);


#ifdef __cplusplus
}
#endif

#endif  /* __DRV_USART_H__ */

